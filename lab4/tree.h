#ifndef ALGO_LABS_TREE_H
#define ALGO_LABS_TREE_H

#ifdef __cplusplus
extern "C" {


#endif

typedef struct node {
    char *key;
    float value;
    int h;

    struct node *l, *r;
} node;

node *createNode(const char *data, float value);

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

float *find(node *t, const char *key);

node *insert(node *t, const char *key, float value);

node *erase(node *t, const char *key);

void clearTree(node *t);

#ifdef __cplusplus
}
#endif


#endif
