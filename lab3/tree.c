#include <stdlib.h>
#include <stdio.h>
#include "structures.h"
#include "stack.h"


node *createNode(typeData x) {
    node *t = (node *) malloc(sizeof(struct node));
    if (!t) {
        printf("Не удалось выделить память\n");
        free(t);
        return NULL;
    }
    t->data = x;
    t->l = t->r = NULL;
    return t;
}


node *buildFromRpn(node *t, stack *rpn, int *i) {
    if (*i == -1) return t;

    typeData cur = rpn->data[*i];
    t = createNode(cur);
    (*i)--;
    if (cur.type == number || cur.type == variable) {
        return t;
    }
    if (cur.type == unary_minus || cur.type == unary_plus) {
        t->l = buildFromRpn(t, rpn, i);
        return t;
    }
    t->l = buildFromRpn(t, rpn, i);
    t->r = buildFromRpn(t, rpn, i);
    return t;
}

void printTree(node *t, int d) {
    if (t == NULL) {
        return;
    }
    for (int i = 0; i < d; i++) {
        printf("  ");
    }
    if (t->data.type == number) {
        printf("%d\n", t->data.num);
    } else if (t->data.type == variable) {
        printf("%s\n", t->data.var);
    } else {
        printf("%s\n", t->data.operator);
    }
    if (t->l != NULL) {
        printTree(t->l, d + 1);
    }
    if (t->r != NULL) {
        printTree(t->r, d + 1);
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
