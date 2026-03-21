#ifndef ALGO_LABS_PARSE_H
#ifdef __cplusplus
extern "C" {
#endif
#define ALGO_LABS_PARSE_H

#include "structures.h"

enumType toEnumType(char c);

int getPriority(typeData c);

stack parse(char *s);

stack toRpn(stack *s);

#endif

#ifdef __cplusplus
}
#endif
