#ifndef ALGO_LABS_TREE_H
#define ALGO_LABS_TREE_H

#ifdef __cplusplus
extern "C" {



#endif

#include <stdbool.h>
#include "structures.h"


node *createNode(typeData x);

node *buildFromRpn(node *t, stack *rpn, int *i);

void printTree(node *t, int d);

void printInfix(node *t);

void clearTree(node *t);

void collect(node *t, stack *a);

typeData *findSame(stack *l, stack *r);

node *removeData(node *t, typeData *element);

node *transform(node *t, bool *done);

node *transformLoop(node *t);

bool subTreeEqual(node *a, node *b);


#ifdef __cplusplus
}
#endif

#endif
