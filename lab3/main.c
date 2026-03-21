#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "structures.h"
#include "parse.h"
#include "tree.h"
#include "stack.h"


signed main() {
    printf("Введите выражение: ");
    char *string = NULL;
    size_t size = 0;
    getline(&string, &size, stdin);
    string[strcspn(string, "\n")] = 0;

    stack s = parse(string);
    stack rpn = toRpn(&s);

    printExpression(&rpn);
    int n = rpn.size - 1;

    node *t = NULL;

    t = buildFromRpn(t, &rpn, &n);
    if (n != -1) {
        printf("Неправильное выражение\n");
        return 2;
    }
    printTree(t, 0);
    printInfix(t);
    printf("\n");

    t = transformLoop(t);

    printTree(t, 0);
    printInfix(t);
    printf("\n");


    // printf("%lu\n", strlen(string));
    // printf("%c", string[size - 1]);
}
