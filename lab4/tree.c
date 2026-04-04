#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

node *createNode(const char *data, float value) {
    node *t = malloc(sizeof(node));
    if (t == NULL) {
        printf("Не удалось выделить память");
        free(t);
        return NULL;
    }
    t->h = 1;
    t->l = t->r = NULL;
    t->value = value;
    t->key = malloc(sizeof(char) * (strlen(data) + 1));
    strcpy(t->key, data);
    return t;
}

void print(node *t, int d) {
    if (t == NULL) {
        return;
    }
    for (int i = 0; i < d; i++) {
        printf("  ");
    }
    printf("%s %.4f\n", t->key, t->value);
    if (t->l != NULL) {
        print(t->l, d + 1);
    }
    if (t->r != NULL) {
        print(t->r, d + 1);
    }
}

int height(node *t) {
    return t ? t->h : 0;
}

void updateHeight(node *t) {
    int hl = height(t->l);
    int hr = height(t->r);
    t->h = (hl > hr ? hl : hr) + 1;
}

int diff(node *a) {
    return height(a->l) - height(a->r);
}

node *rightRotate(node *a) {
    node *b = a->l;
    a->l = b->r;
    b->r = a;
    updateHeight(a);
    updateHeight(b);
    return b;
}


node *leftRotate(node *a) {
    node *b = a->r;
    a->r = b->l;
    b->l = a;
    updateHeight(a);
    updateHeight(b);
    return b;
}

node *rightBigRotate(node *a) {
    a->l = leftRotate(a->l);
    return rightRotate(a);
}

node *leftBigRotate(node *a) {
    a->r = rightRotate(a->r);
    return leftRotate(a);
}

node *balance(node *a) {
    if (diff(a) == -2) {
        if (diff(a->r) > 0) {
            return leftBigRotate(a);
        }
        return leftRotate(a);
    }
    if (diff(a) == 2) {
        if (diff(a->l) < 0) {
            return rightBigRotate(a);
        }
        return rightRotate(a);
    }
    return a;
}


float *find(node *t, const char *key) {
    if (t == NULL) {
        return NULL;
    }
    if (strcmp(t->key, key) == 0) {
        return &t->value;
    }

    if (strcmp(t->key, key) > 0) {
        return find(t->l, key);
    }
    return find(t->r, key);
}

node *insert(node *t, const char *key, float value) {
    if (t == NULL) {
        return createNode(key, value);
    }
    if (strcmp(t->key, key) == 0) {
        return t;
    }
    if (strcmp(t->key, key) > 0) {
        t->l = insert(t->l, key, value);
    } else {
        t->r = insert(t->r, key, value);
    }
    updateHeight(t);
    return balance(t);
}

node *findMin(node *t) {
    while (t && t->l) t = t->l;
    return t;
}

node *erase(node *t, const char *key) {
    if (t == NULL) {
        return NULL;
    }
    if (strcmp(t->key, key) == 0) {
        if (t->l == NULL) {
            node *tmp = t->r;
            free(t->key);
            free(t);
            return tmp;
        }
        if (t->r == NULL) {
            node *tmp = t->l;
            free(t->key);
            free(t);
            return tmp;
        }
        node *temp = findMin(t->r);
        free(t->key);
        t->key = strdup(temp->key);
        t->value = temp->value;
        t->r = erase(t->r, temp->key);
    } else if (strcmp(t->key, key) > 0) {
        t->l = erase(t->l, key);
    } else {
        t->r = erase(t->r, key);
    }
    updateHeight(t);
    return balance(t);
}

void clearTree(node *t) {
    if (t == NULL) {
        return;
    }
    clearTree(t->l);
    clearTree(t->r);
    free(t->key);
    free(t);
}
