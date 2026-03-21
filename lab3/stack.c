#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"


void pushNode(nodeStack *s, node *x) {
    if (s->size == s->capacity) {
        s->capacity *= 2;
        s->data = realloc(s->data, sizeof(node) * s->capacity);
    }
    s->data[s->size] = *x;
    s->size++;
}

void initNodeStack(nodeStack *s) {
    s->size = 0;
    s->capacity = 4;
    s->data = malloc(sizeof(node) * s->capacity);
    if (!s->data) {
        printf("Не удалось выделить память\n");
        free(s->data);
        exit(-1);
    }
}

void initStack(stack *s) {
    s->size = 0;
    s->capacity = 4;
    s->data = malloc(sizeof(typeData) * s->capacity);
    if (!s->data) {
        printf("Не удалось выделить память\n");
        free(s->data);
        exit(-1);
    }
}

typeData *back(stack *s) {
    if (s->size == 0) {
        return NULL;
    }
    return &s->data[s->size - 1];
}

void push(stack *s, typeData x) {
    if (s->size == s->capacity) {
        s->capacity *= 2;
        s->data = realloc(s->data, sizeof(typeData) * s->capacity);
    }
    typeData *t = &s->data[s->size];
    t->type = x.type;
    if (x.type == number) {
        t->num = x.num;
    } else if (x.type == variable) {
        t->var = malloc(sizeof(char) * (strlen(x.var) + 1));
        strcpy(t->var, x.var);
    } else {
        t->sign = malloc(sizeof(char) * (strlen(x.sign) + 1));
        strcpy(t->sign, x.sign);
    }
    s->size++;
}

typeData *pop(stack *s) {
    if (s->size == 0) {
        printf("Стек пустой\n");
        return NULL;
    }
    s->size--;
    typeData *t = &s->data[s->size];
    typeData *x = malloc(sizeof(typeData));
    if (!x) {
        printf("Не удалось выделить память\n");
        return NULL;
    }
    x->type = t->type;
    if (t->type == number) {
        x->num = t->num;
    } else if (t->type == variable) {
        x->var = malloc(sizeof(char) * (strlen(t->var) + 1));
        if (!x->var) {
            printf("Не удалось выделить память\n");
            free(x->var);
            return NULL;
        }
        strcpy(x->var, t->var);
        free(t->var);
    } else {
        x->sign = malloc(sizeof(char) * (strlen(t->sign) + 1));
        if (!x->sign) {
            printf("Не удалось выделить память\n");
            free(x->sign);
            return NULL;
        }
        strcpy(x->sign, t->sign);
        free(t->sign);
    }
    return x;
}

void freeStack(stack *s) {
    for (int i = 0; i < s->size; i++) {
        typeData *td = &s->data[i];
        if (td->type == variable) {
            free(td->var);
        } else if (td->type != number) {
            free(td->sign);
        }
    }
    free(s->data);
    s->size = s->capacity = 0;
}

void printStack(stack *s) {
    for (int i = 0; i < s->size; i++) {
        typeData *td = &s->data[i];
        if (td->type == variable) {
            printf("(%s %d) ", td->var, td->type);
        } else if (td->type == number) {
            printf("(%d %d) ", td->num, td->type);
        } else {
            printf("(%s %d) ", td->sign, td->type);
        }
    }
    printf("\n");
}

void printExpression(stack *s) {
    for (int i = 0; i < s->size; i++) {
        typeData *td = &s->data[i];
        if (td->type == variable) {
            printf("%s ", td->var);
        } else if (td->type == number) {
            printf("%d ", td->num);
        } else {
            if (td->type == unary_minus) {
                printf("~ ");
            } else if (td->type == unary_plus) {
                printf("$ ");
            } else {
                printf("%s ", td->sign);
            }
        }
    }
    printf("\n");
}
