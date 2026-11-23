#ifndef ARGUMENT_H
#define ARGUMENT_H

typedef struct 
{
    const char *name;
    int min, max; // max = -1 para argumentos infinitos
    char **argv;
    int argc;
} clic_root_argument;

clic_root_argument new_argument(const char*name,int min, int max);

#endif