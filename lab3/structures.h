#ifndef ALGO_LABS_STRUCTURES_H
#define ALGO_LABS_STRUCTURES_H

#ifdef __cplusplus
extern "C" {



#endif

typedef enum enumType {
    number = 0,
    variable = 1,
    unary_plus = 2,
    unary_minus = 3,
    bracket = 4,
    multiply = 5,
    division = 6,
    power = 7,
    plus = 8,
    minus = 9,
} enumType;

typedef struct typeData {
    enumType type;

    union {
        int num;
        char *sign;
        char *var;
    };
} typeData;

typedef struct node {
    typeData data;
    struct node *l, *r;
} node;

typedef struct stack {
    typeData *data;
    int size;
    int capacity;
} stack;

typedef struct nodeStack {
    node *data;
    int size;
    int capacity;
} nodeStack;


typeData createNumber(int n);

typeData createVariable(char *v);

typeData createOperator(char *x, enumType type);

void printTypeData(typeData data);

#ifdef __cplusplus
}
#endif
#endif
