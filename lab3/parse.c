#include <ctype.h>
#include <stdbool.h>

#include "structures.h"
#include "stack.h"

enumType toEnumType(char c) {
    switch (c) {
        case '+': return plus;
        case '-': return minus;
        case '*': return multiply;
        case '/': return division;
        case '^': return power;
        default: return number;
    }
}


int getPriority(typeData c) {
    int a[10] = {0, 0, 5, 5, 5, 3, 3, 4, 2, 2};
    return a[c.type];
}

stack parse(char *s) {
    int i = 0;
    int n = strlen(s);
    stack ans;
    initStack(&ans);

    bool wait = true;

    while (i < n) {
        if (isspace(s[i])) {
            i++;
        } else if (isdigit(s[i])) {
            int num = 0;
            while (isdigit(s[i])) {
                num = num * 10 + (s[i] - '0');
                i++;
            }
            push(&ans, createNumber(num));
            wait = false;
        } else if (isalpha(s[i])) {
            int st = i;
            while (i < n && !strchr("+-*/^ )(", s[i])) {
                i++;
            }
            int len = i - st;
            char *str = malloc(sizeof(char) * (len + 1));
            strncpy(str, s + st, len);
            str[len] = '\0';
            push(&ans, createVariable(str));
            wait = false;
            free(str);
        } else if (s[i] == '(' || s[i] == ')') {
            char t[2] = {s[i], '\0'};
            push(&ans, createOperator(t, bracket));
            wait = (s[i] == '(');
            i++;
        } else if (strchr("+-*/^", s[i])) {
            enumType type = toEnumType(s[i]);
            if (s[i] == '+' && wait) {
                type = unary_plus;
            } else if (s[i] == '-' && wait) {
                type = unary_minus;
            }
            char t[2] = {s[i], '\0'};
            push(&ans, createOperator(t, type));
            i++;
            wait = true;
        } else {
            printf("Неизвестный символ\n");
            exit(-1);
        }
    }
    return ans;
}

stack toRpn(stack *s) {
    stack out, st;
    initStack(&out);
    initStack(&st);

    int len = s->size;

    for (int i = 0; i < len; i++) {
        typeData cur = s->data[i];

        if (cur.type == number || cur.type == variable) {
            push(&out, cur);
        } else if (cur.type == bracket) {
            if (strcmp(cur.operator, "(") == 0) {
                push(&st, cur);
            } else {
                bool ok = false;
                while (st.size > 0) {
                    typeData t = pop(&st);
                    if (t.type == bracket && strcmp(cur.operator, ")") == 0) {
                        ok = true;
                        break;
                    }
                    push(&out, t);
                }
                if (!ok) {
                    printf("Неправильное выражение\n");
                    exit(-1);
                }
            }
        } else {
            int priority = getPriority(cur);
            while (st.size > 0) {
                typeData *top = back(&st);
                if (top->type == bracket) break;
                int topPriority = getPriority(*top);
                if (topPriority > priority) {
                    typeData t = pop(&st);
                    push(&out, t);
                } else {
                    break;
                }
            }
            push(&st, cur);
        }
    }
    while (st.size > 0) {
        typeData t = pop(&st);
        if (t.type == bracket && strcmp(t.operator, "(") == 0) {
            printf("Неправильное выражение\n");
            exit(-1);
        }
        push(&out, t);
    }
    freeStack(&st);
    return out;
}
