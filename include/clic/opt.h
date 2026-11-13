#ifndef CLIC_OPT_H
#define CLIC_OPT_H

#include <stdbool.h>
#include "clic/argument.h"

typedef struct clic_opt clic_option;

typedef int (*opt_action_fn)(clic_option *option, void *user_data);

struct clic_opt
{
    char short_name;
    const char *long_name;
    // const char **aliases; Fica de promessa
    const char *description;
    bool was_set;
    bool required;
    clic_argument arguments;
    opt_action_fn opt_action;
    clic_option *next;
};

clic_option clic_new_option(char short_name, const char *long_name, const char *description, clic_type type, opt_action_fn action, bool required);

int clic_add_option(clic_option *option);

#endif