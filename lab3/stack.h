#ifndef ALGO_LABS_STACK_H
#define ALGO_LABS_STACK_H
#include "structures.h"

void initStack(stack *s);

typeData *back(stack *s);

void push(stack *s, typeData x);

typeData pop(stack *s);

void freeStack(stack *s);

void printStack(stack *s);

#endif
