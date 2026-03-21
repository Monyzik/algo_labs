#ifndef ALGO_LABS_STACK_H
#define ALGO_LABS_STACK_H
#ifdef __cplusplus
extern "C" {


#endif
#include "structures.h"

void initStack(stack *s);

void pushNode(nodeStack *s, node *x);

void initNodeStack(nodeStack *s);

typeData *back(stack *s);

void push(stack *s, typeData x);

typeData *pop(stack *s);

void freeStack(stack *s);

void printStack(stack *s);

void printExpression(stack *s);

#ifdef __cplusplus
}
#endif

#endif
