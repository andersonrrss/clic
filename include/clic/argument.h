#ifndef ARGUMENT_H
#define ARGUMENT_H

#include "clic/types.h"

typedef struct 
{
    const char *name;
    int min, max; // max = -1 para argumentos infinitos
    clic_type type;
    char **argv;
    int argc;
} clic_argument;

clic_argument new_argument(const char*name, clic_type type, int min, int max);

#endif