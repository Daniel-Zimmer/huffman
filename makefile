CC = gcc
CARGS = -Wall

build: huffman

clean:
	rm heap.o stack.o huffman

huffman: huffman.c heap.o stack.o btree.o
	$(CC) $(CARGS) huffman.c \
		heap.o stack.o btree.o \
		-o huffman

heap.o: heap.c heap.h
	$(CC) $(CARGS) heap.c -c

stack.o: stack.c stack.h
	$(CC) $(CARGS) stack.c -c

btree.o: btree.c btree.h
	$(CC) $(CARGS) btree.c -c