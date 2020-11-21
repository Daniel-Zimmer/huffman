#include "heap.h"

#include <stdio.h>
#include <stdlib.h>

#define INIT_CAPACITY 160

struct heap {
	int len;
	int capacity;
	int (*compFunc) (void *a, void *b);
	void *data[];
};

static void up(Heap *h, int i) {
	int p = (i - 1) / 2;
	// comp data[i] < data[p]
	if (p >= 0 && h->compFunc(h->data[i], h->data[p])) {
		void *aux = h->data[i];
		h->data[i] = h->data[p];
		h->data[p] = aux;
		up(h, p);
	}
}

static void down(Heap *h, int i) {
	int f1 = 2 * i + 1;
	if (f1 >= h->len) {
		return;
	}
	int f2 = f1 + 1;
	if (f2 < h->len) {
		if (h->compFunc(h->data[f2], h->data[f1]) && h->compFunc(h->data[f2], h->data[i])) {
			void *aux = h->data[i];
			h->data[i] = h->data[f2];
			h->data[f2] = aux;
			down(h, f2);
			return;
		}
	}
	if (h->compFunc(h->data[f1], h->data[i])) {
		void *aux = h->data[i];
		h->data[i] = h->data[f1];
		h->data[f1] = aux;
		down(h, f1);
	}
}

Heap *HEAP_create(int (*compFunc) (void *a, void *b)) {
	Heap* h = malloc(sizeof(Heap) + sizeof(void *) * INIT_CAPACITY);

	h->compFunc = compFunc;
	h->capacity = INIT_CAPACITY;
	h->len = 0;

	return h;
}

Heap *HEAP_insert(Heap *h, void *val) {
	if (h->len == h->capacity) {
		h->capacity <<= 2;
		h = realloc(h, sizeof(Heap) + sizeof(void*) * h->capacity);
	}

	h->data[h->len] = val;
	up(h, (h->len)++);

	return h;
}

void *HEAP_remove(Heap *h) {
	void *val = h->data[0];

	h->data[0] = h->data[--(h->len)];
	down(h, 0);

	return val;
}

Heap *HEAP_construct(void *vet[], int n, int (*compFunc) (void *a, void *b)) {
	Heap *h = HEAP_create(compFunc);

	for (int i = n / 2 - 1; i >= 0; i--) {
		down(h, i);
	}

	return h;
}

int HEAP_len(Heap *h) { return h->len; }

// void heap_sort(int vet[], int n) {
// 	construir2(vet, n);
// 	for (int i = n - 1; i >= 0; i--) {
// 		int val = vet[0];
// 		remover(vet, n--);
// 		vet[i] = val;
// 	}
// }
