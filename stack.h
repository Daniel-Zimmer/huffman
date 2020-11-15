#ifndef STACK_H
#define STACK_H

typedef struct stack Stack;

Stack *STACK_create();
Stack *STACK_push(Stack *s, void* val);
void  *STACK_pop(Stack *s);
int    STACK_len(Stack *s);

#endif // STACK_H