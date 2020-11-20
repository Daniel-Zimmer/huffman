#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

#define INIT_CAPACITY 16

struct stack {
	int len;
	int capacity;
	void *data[];
};

Stack *STACK_create() {
	Stack *s = malloc(sizeof(Stack) + sizeof(void *) * INIT_CAPACITY);

	s->len = 0;
	s->capacity = INIT_CAPACITY;

	return s;
}

Stack *STACK_push(Stack *s, void* val) {
	if (s->len == s->capacity) {
		s->capacity <<= 1;
		s = realloc(s, sizeof(Stack) + sizeof(void *) * s->capacity);
	}

	s->data[s->len++] = val;

	return s;
}

void *STACK_pop(Stack *s) {
	return s->data[--s->len];
}

int STACK_len(Stack *s) { return s->len; };


