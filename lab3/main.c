#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parse.c"
#include "tree.c"


signed main() {
    char *string = NULL;
    size_t size = 0;
    getline(&string, &size, stdin);
    // printf("%s", string);
    string[strcspn(string, "\n")] = 0;

    stack s = parse(string);

    printStack(&s);


    stack rpn = toRpn(&s);

    printStack(&rpn);
    int n = rpn.size - 1;

    node *t = NULL;

    t = buildFromRpn(t, &rpn, &n);
    printTree(t, 1);

    // printf("%lu\n", strlen(string));
    // printf("%c", string[size - 1]);


}
