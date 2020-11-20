#include <stdio.h>
#include <stdlib.h>

#include "heap.h"
#include "stack.h"
#include "btree.h"
#include "bit.h"

typedef struct character {
	int count;
	char isLeaf;
	char c;
} Character;

typedef struct encoding {
	unsigned char len;
	unsigned char val;
} Encoding;

int HeapCompFunc(void *a, void *b) {
	Character *charA = (Character *) ((Node *) a)->data;
	Character *charB = (Character *) ((Node *) b)->data;

	int countA = charA->count;
	int countB = charB->count;

	if (countA == countB) {
		if (!charA->isLeaf) {
			if (charB->isLeaf) {
				countA++;
			}
		} else { // charA.isLeaf
			if (!charB->isLeaf) {
				countB++;
			} else { // charA.isLeaf && charB.isLeaf
				return charA->c < charB->c;
			}
		}
	}

	return countA < countB;
}

int traverse(Node *n, Encoding *encs, char val, char len) {
	int sizeLeft, sizeRight;

	if (n->left) {
		sizeLeft = traverse(n->left, encs, val<<1, len+1);
	}
	if (n->right) {
		sizeRight = traverse(n->right, encs, (val<<1) | 1, len+1);
	}

	Character *c = n->data;

	if (c->isLeaf) {
		encs[c->c].val = val;
		encs[c->c].len = len;

		return c->count * len;
	}

	return sizeLeft + sizeRight;
}

void headerTraverse(Node *n, Encoding *encs, char *header, int *headerIdx) {
	if (n->left) {
		headerTraverse(n->left, encs, header, headerIdx);
	}
	if (n->right) {
		headerTraverse(n->right, encs, header, headerIdx);
	}

	Character *c = n->data;

	if (c->isLeaf) {

		BIT_write(header, (*headerIdx)++, 1);
		
		for(int i = 7; i >=0; i--) {
			BIT_write(header, (*headerIdx)++, (c->c >> i) & 1);
		}

	} else {
		BIT_write(header, (*headerIdx)++, 0);
	}

}

int main(int argc, char **argv) {

	if (argc != 4) {
		printf("usage: huffman -e|-d [input file] [output file]\n");
		return 1;
	}


	if (argv[1][1] == 'e') {
		FILE *input = fopen(argv[2], "r");
		fseek(input, 0, SEEK_END);
		long inputSize = ftell(input);
		rewind(input);

		char *inputData = malloc(inputSize);
		fread(inputData, inputSize, 1, input);

		Character c[256];

		for (int i = 0; i < 256; i++) {
			c[i].c = i;
			c[i].count = 0;
			c[i].isLeaf = 1;
		}

		for (int i = 0; i < inputSize; i++) {
			c[(int) inputData[i]].count++;
		}

		Heap *h = HEAP_create(HeapCompFunc);

		for (int i = 0; i < 256; i++) {
			if (c[i].count != 0) {
				Node *n = BTREE_create(&c[i]);
				h = HEAP_insert(h, n);
			}
		}

		while (HEAP_len(h) > 1) {
			Node *right = HEAP_remove(h);
			Node *left  = HEAP_remove(h);

			Character *ch = malloc(sizeof(Character));
			ch->isLeaf = 0;
			ch->count =
				((Character *) left )->count +
				((Character *) right)->count;
			
			Node *p = BTREE_create(ch);
			p->left  = left;
			p->right = right;

			h = HEAP_insert(h, p);
		}

		Encoding encs[256];

		Node *n = HEAP_remove(h);

		int bitCount = traverse(n, encs, 0, 0) + 1;

		int bitOffset = ((8 - (bitCount%8))%8);
		// round up bits to multiple of 8
		int byteCount = (bitCount+bitOffset)/8;

		char *outputData = malloc(byteCount);

		int outputIdx = bitOffset;
		BIT_write(outputData, outputIdx++, 1);
		for (int i = 0 ; i < inputSize; i++) {
			Encoding enc = encs[inputData[i]];
			printf("%c - %x - %d\n", inputData[i], enc.val, enc.len);

			for (int j = enc.len; j >= 0 ; j--) {
				BIT_write(outputData, outputIdx++, (enc.val >> j) & 1);
			}
		}

		char *header = malloc(512);

		int headerIdx = 0;

		headerTraverse(n, encs, header, &headerIdx);

		FILE *output = fopen(argv[3], "w+");

		fwrite(header, (headerIdx+7)/8, 1, output);
		fwrite(outputData, byteCount, 1, output);

	} else if (argv[1][1] == 'd'){
		
		FILE *input = fopen(argv[2], "r");
		fseek(input, 0, SEEK_END);
		long inputSize = ftell(input);
		rewind(input);

		char *inputData = malloc(inputSize);
		fread(inputData, inputSize, 1, input);
		
		Stack *s = STACK_create();

		union {
			char c[4];
			int i;
		} uu;
		uu.c[0] = inputData[0];
		uu.c[1] = inputData[1];
		uu.c[2] = inputData[2];
		uu.c[3] = inputData[3];

		union {
			char c[2];
			short s;
		} u;

		int bits = 0;
		char bit = 0;
		int inputIdx = 4;

		u.c[0] = inputData[inputIdx];

		for (int i = 0; i < uu.i - 4; i++) {
			if (bits == 8) {
				inputIdx++;
				u.c[0] = inputData[inputIdx];
				bits = 0;
			}

			u.s <<= 1;
			bit = u.c[1] & 1;
			bits++;
			if (bit == 1) {
				char ascii = 0;
				for (int i = 0; i < 8; i++) {

					if (bits == 8) {
						inputIdx++;
						u.c[0] = inputData[inputIdx];
						bits = 0;
					}

					u.s <<= 1;
					bit = (u.c[1] & 1);
					bits++;

					ascii <<= 1;
					ascii |= bit;
				}

				Character *ch = malloc(sizeof(Character));
				ch->isLeaf = 1;
				ch->c = ascii;
				Node *n = BTREE_create(ch);
				s = STACK_push(s, n);
				
			} else {
				if (STACK_len(s) == 1) {
					break;
				}
				Node *right = STACK_pop(s);
				Node *left  = STACK_pop(s);

				Character *ch = malloc(sizeof(Character));
				ch->isLeaf = 0;
				Node *p = BTREE_create(ch);
				p->left = left;
				p->right = right;

				s = STACK_push(s, p);
			}
		}


		Node *tree = STACK_pop(s);

		printf("%p\n", tree);

		

	} else {

		printf("usage: huffman -e|-d [input file] [output file]\n");
		return 1;

	}

	return 0;
}
