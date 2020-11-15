#include "btree.h"

#include <stdio.h>
#include <stdlib.h>

Node *BTREE_create(void *val) {
	Node *n = malloc(sizeof(Node));

	n->left  = NULL;
	n->right = NULL;
	n->data = val;

	return n;
}

Node *BTREE_insertLeft(Node *n, void *val) {
	n->left = BTREE_create(val);

	return n->left;
}

Node *BTREE_insertRight(Node *n, void *val) {
	n->right = BTREE_create(val);

	return n->right;
}

void BTREE_traversePost(Node *n, void (*func) (void *)) {
	if (n->left) {
		BTREE_traversePost(n->left, func);
	}
	if (n->right) {
		BTREE_traversePost(n->right, func);
	}
	func(n->data);
}
