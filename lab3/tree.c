#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
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

bool subTreeEqual(node *a, node *b) {
    if (a == NULL && b == NULL) {
        return true;
    }
    if (a == NULL || b == NULL) {
        return false;
    }
    if (a->data.type != b->data.type) {
        return false;
    }
    if (a->data.type == variable && strcmp(a->data.var, b->data.var) != 0) {
        return false;
    }

    if (a->data.type == number && a->data.num != b->data.num) {
        return false;
    }

    if ((a->data.type != variable && a->data.type != number) && strcmp(a->data.sign, b->data.sign) != 0) {
        return false;
    }


    return subTreeEqual(a->l, b->l) && subTreeEqual(a->r, b->r);
}


node *buildFromRpn(node *t, stack *rpn, int *i) {
    if (*i == -1) return NULL;

    typeData cur = rpn->data[*i];
    t = createNode(cur);
    (*i)--;
    if (cur.type == number || cur.type == variable) {
        return t;
    }
    if (cur.type == unary_minus || cur.type == unary_plus) {
        t->r = buildFromRpn(t, rpn, i);
        if (t->r == NULL) {
            printf("Неправильное выражение\n");
            exit(2);
        }
        return t;
    }
    t->r = buildFromRpn(t, rpn, i);
    if (t->r == NULL) {
        printf("Неправильное выражение\n");
        exit(2);
    }
    t->l = buildFromRpn(t, rpn, i);
    if (t->l == NULL) {
        printf("Неправильное выражение\n");
        exit(2);
    }
    return t;
}

void printTree(node *t, int d) {
    if (t == NULL) {
        return;
    }
    for (int i = 0; i < d; i++) {
        printf("  ");
    }
    printTypeData(t->data);
    printf("\n");
    if (t->l != NULL) {
        printTree(t->l, d + 1);
    }
    if (t->r != NULL) {
        printTree(t->r, d + 1);
    }
}

void printInfix(node *t) {
    if (t == NULL) return;
    if (t->l == NULL && t->r == NULL) {
        printTypeData(t->data);
        return;
    }
    printf("(");
    printInfix(t->l);

    if (t->data.type != unary_minus && t->data.type != unary_plus) {
        printf(" ");
        printTypeData(t->data);
        printf(" ");
    } else {
        printTypeData(t->data);
    }

    printInfix(t->r);

    printf(")");
}

void clearTree(node *t) {
    if (t == NULL) {
        return;
    }
    clearTree(t->l);
    clearTree(t->r);
    free(t);
}


void collect(node *t, nodeStack *a) {
    if (t == NULL) return;
    pushNode(a, t);
    if (t->data.type == multiply) {
        collect(t->l, a);
        collect(t->r, a);
    }
}

node *findSame(nodeStack *l, nodeStack *r) {
    for (int i = 0; i < l->size; i++) {
        for (int j = 0; j < r->size; j++) {
            if (l->data[i].data.type == number && l->data[i].data.num == 1) continue;
            if (subTreeEqual(&l->data[i], &r->data[j])) {
                return &l->data[i];
            }
        }
    }
    return NULL;
}

node *removeData(node *t, node *element, bool *done) {
    if (t == NULL) return NULL;
    if (*done) return t;

    if (*done && (t->data.type == variable || t->data.type == number)) {
        return t;
    }

    if (subTreeEqual(t, element)) {
        *done = true;
        return NULL;
    }
    if (t->data.type == multiply) {
        node *nl = removeData(t->l, element, done);
        node *nr = removeData(t->r, element, done);
        if (!nl && !nr) return NULL;
        if (!nl) return nr;
        if (!nr) return nl;
        t->l = nl;
        t->r = nr;
        return t;
    }


    *done = false;
    t->l = removeData(t->l, element, done);
    *done = false;
    t->r = removeData(t->r, element, done);
    return t;
}

node *transform(node *t, bool *done) {
    if (t == NULL) return NULL;

    if (t->data.type == minus) {
        nodeStack ls, rs;
        initNodeStack(&ls);
        initNodeStack(&rs);
        collect(t->l, &ls);
        collect(t->r, &rs);
        node *v = findSame(&ls, &rs);
        if (v != NULL) {
            bool d1 = false, d2 = false;
            node *lrm = removeData(t->l, v, &d1);
            node *rrm = removeData(t->r, v, &d2);
            if (!lrm) lrm = createNode(createNumber(1));
            if (!rrm) rrm = createNode(createNumber(1));

            node *nt = createNode(createOperator("*", multiply));
            nt->l = v;
            nt->r = createNode(createOperator("-", minus));


            nt->r->l = lrm;
            nt->r->r = rrm;

            // printInfix(nt);
            // printf("\n");

            nt->r = transform(nt->r, done);
            *done = true;

            return nt;
        }
    }
    t->l = transform(t->l, done);
    t->r = transform(t->r, done);
    return t;
}

node *transformLoop(node *t) {
    bool done = true;
    while (done) {
        done = false;
        t = transform(t, &done);
        // printInfix(t);
        // printf("\n");
    }
    return t;
}
