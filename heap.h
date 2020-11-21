#ifndef HEAP_H
#define HEAP_H

typedef struct heap Heap;

Heap *HEAP_create(int (*compFunc) (void *a, void *b));
Heap *HEAP_insert(Heap *h, void *val);
void *HEAP_remove(Heap *h);
Heap *HEAP_construct(void *vet[], int n, int (*compFunc) (void *a, void *b));
int   HEAP_len(Heap *h);

#endif // HEAP_H