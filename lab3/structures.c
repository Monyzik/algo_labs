#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "structures.h"


typeData createNumber(int n) {
    typeData data;
    data.type = number;
    data.num = n;
    return data;
}

typeData createVariable(char *v) {
    typeData data;
    data.type = variable;
    data.var = malloc(sizeof(char) * (strlen(v) + 1));
    if (!data.var) {
        printf("Не удалось выделить память\n");
        free(data.var);
        exit(-1);
    }
    strcpy(data.var, v);
    return data;
}

typeData createOperator(char *x, enumType type) {
    typeData data;
    data.type = type;
    data.sign = malloc(sizeof(char) * (strlen(x) + 1));
    if (!data.sign) {
        printf("Не удалось выделить память\n");
        free(data.sign);
        exit(-1);
    }
    strcpy(data.sign, x);
    return data;
}

void printTypeData(typeData data) {
    if (data.type == number) {
        printf("%d", data.num);
    } else if (data.type == variable) {
        printf("%s", data.var);
    } else {
        printf("%s", data.sign);
    }
}
