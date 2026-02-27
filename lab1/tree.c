#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>


typedef int type;

typedef struct node {
    type data;
    struct node *l, *r;
} node;

node *createNode(type x);

node *insert(node *t, type x);

node *erase(node *t, type x);

node *findMin(node *t);

int depth(node *t);

int max(int a, int b);

bool query(node *t, int d, int maxDepth);

bool isLeaf(node *t);

void print(node *t, int d);

void clearTree(node *t);


node *createNode(type x) {
    node *t = (node *) malloc(sizeof(struct node));
    if (!t) {
        printf("Не получилось выделить память\n");
        free(t);
        return NULL;
    }
    t->data = x;
    t->l = t->r = NULL;
    return t;
}

bool query(node *t, int d, int maxDepth) {
    if (t == NULL) return true;
    if (isLeaf(t)) {
        return d == maxDepth;
    }
    return query(t->l, d + 1, maxDepth) && query(t->r, d + 1, maxDepth);
}

int depth(node *t) {
    if (t == NULL) {
        return 0;
    }
    return max(depth(t->l), depth(t->r)) + 1;
}

int max(int a, int b) {
    return a > b ? a : b;
}

node *insert(node *t, type x) {
    if (t == NULL) {
        return createNode(x);
    }
    if (x < t->data) {
        t->l = insert(t->l, x);
    } else if (x > t->data) {
        t->r = insert(t->r, x);
    }
    return t;
}

node *findMin(node *t) {
    if (t == NULL) return NULL;
    while (t->l != NULL) {
        t = t->l;
    }
    return t;
}

bool isLeaf(node *t) {
    return t->l == NULL && t->r == NULL;
}

node *erase(node *t, type x) {
    if (t == NULL) {
        printf("Не удалось найти нужный элемент\n");
        return NULL;
    }
    if (t->data == x) {
        if (t->l == NULL) {
            node *temp = t->r;
            free(t);
            return temp;
        }
        if (t->r == NULL) {
            node *temp = t->l;
            free(t);
            return temp;
        }
        node *temp = findMin(t->r);
        t->data = temp->data;
        t->r = erase(t->r, temp->data);
    } else if (t->data > x) {
        t->l = erase(t->l, x);
    } else {
        t->r = erase(t->r, x);
    }
    return t;
}

void print(node *t, int d) {
    if (t == NULL) {
        return;
    }
    for (int i = 0; i < d; i++) {
        printf("  ");
    }
    printf("%d\n", t->data);
    if (t->l != NULL) {
        print(t->l, d + 1);
    }
    if (t->r != NULL) {
        print(t->r, d + 1);
    }
}

void clearTree(node *t) {
    if (t == NULL) {
        return;
    }
    clearTree(t->l);
    clearTree(t->r);
    free(t);
}
