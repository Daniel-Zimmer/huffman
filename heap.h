#ifndef HEAP_H
#define HEAP_H

#define INIT_CAPACITY 16

typedef struct heap Heap;

Heap *HEAP_create(int (*compFunc) (void *a, void *b));
Heap *HEAP_insert(Heap *h, void *val);
void *HEAP_remove(Heap *h);
Heap *HEAP_construct(int vet[], int n, int (*compFunc) (void *a, void *b));

#endif // HEAP_H