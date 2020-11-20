CC = gcc
CARGS = -Wall -Wno-char-subscripts -g

build: huffman

clean:
	rm huffman heap.o stack.o btree.o bit.o

huffman: huffman.c heap.o stack.o btree.o bit.o
	$(CC) $(CARGS) huffman.c \
		heap.o stack.o btree.o bit.o\
		-o huffman

heap.o: heap.c heap.h
	$(CC) $(CARGS) heap.c -c

stack.o: stack.c stack.h
	$(CC) $(CARGS) stack.c -c

btree.o: btree.c btree.h
	$(CC) $(CARGS) btree.c -c

bit.o: bit.c bit.h
	$(CC) $(CARGS) bit.c -c