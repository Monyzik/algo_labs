#ifndef ALGO_LABS_TREE_H
#define ALGO_LABS_TREE_H

#ifdef __cplusplus
extern "C" {

#endif

typedef int type_value;
typedef int type_key;

typedef struct node {
    type_key key;
    type_value value;
    int h;

    struct node *l, *r;
} node;

node *createNode(type_key data, type_value value);

void print(node *t, int d);

int diff(node *a);

int height(node *t);

void updateHeight(node *t);

node *findMin(node *t);

node *rightRotate(node *a);

node *leftRotate(node *a);

node *rightBigRotate(node *a);

node *leftBigRotate(node *a);

node *balance(node *a);

type_value *find(node *t, type_key key);

node *insert(node *t, type_key key, type_key value);

node *erase(node *t, type_key key);

void clearTree(node *t);

#ifdef __cplusplus
}
#endif


#endif
