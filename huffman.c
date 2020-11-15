#include <stdio.h>
#include <stdlib.h>

#include "heap.h"
#include "stack.h"
#include "btree.h"

// typedef struct node {
// 	int count;
// 	char c;
// 	char isChar;
// 	struct node *left;
// 	struct node *right;
// } Node;

int compFunc(void *a, void *b) {
	int m = ((Node *) a)->count;
	int n = ((Node *) b)->count;

	return m < n;
}

int main(int argc, char **argv) {

	if (argc != 2) {
		printf("usage: huffman [file]\n");
		return 1;
	}

	FILE *input = fopen(argv[1], "r");
	fseek(input, 0, SEEK_END);
	long inputSize = ftell(input);
	rewind(input);

	char *inputData = malloc(inputSize);
	fread(inputData, inputSize, 1, input);
	printf("%s\n", inputData);

	return 0;
}
