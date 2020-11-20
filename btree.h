#ifndef BTREE_H
#define BTREE_H

struct node {
	struct node *left;
	struct node *right;
	void *data;
};

typedef struct node Node;

Node *BTREE_create(void *val);
Node *BTREE_insertLeft(Node *n, void *val);
Node *BTREE_insertRight(Node *n, void *val);
void  BTREE_traversePost(Node *n, void (*func) (void *));

#endif // BTREE_H