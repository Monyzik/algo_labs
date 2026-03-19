#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"


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
        t->operator = malloc(sizeof(char) * (strlen(x.operator) + 1));
        strcpy(t->operator, x.operator);
    }
    s->size++;
}

typeData pop(stack *s) {
    if (s->size == 0) {
        printf("Стек пустой\n");
        exit(-1);
    }
    s->size--;
    typeData *t = &s->data[s->size];
    typeData x;
    x.type = t->type;
    if (t->type == number) {
        x.num = t->num;
    } else if (t->type == variable) {
        x.var = malloc(sizeof(char) * (strlen(t->var) + 1));
        if (!x.var) {
            printf("Не удалось выделить память\n");
            free(x.var);
            exit(-1);
        }
        strcpy(x.var, t->var);
        free(t->var);
    } else {
        x.operator = malloc(sizeof(char) * (strlen(t->operator) + 1));
        if (!x.operator) {
            printf("Не удалось выделить память\n");
            free(x.operator);
            exit(-1);
        }
        strcpy(x.operator, t->operator);
        free(t->operator);
    }
    return x;
}

void freeStack(stack *s) {
    for (int i = 0; i < s->size; i++) {
        typeData *td = &s->data[i];
        if (td->type == variable) {
            free(td->var);
        } else if (td->type != number) {
            free(td->operator);
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
            printf("(%s %d) ", td->operator, td->type);
        }
    }
    printf("\n");
}
