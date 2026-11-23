#ifndef CLIC_OPT_H
#define CLIC_OPT_H

#include <stdbool.h>

#include "clic/arity.h"
#include "clic/error.h"

typedef struct clic_opt clic_opt;

typedef int (*opt_action_fn)(clic_opt *option, void *user_data);

clic_error clic_opt_new(struct clic_opt **out, const char *raw_short, const char *raw_long, const char *description, 
                      clic_value_arity arity, opt_action_fn action, bool required);

void clic_opt_free_all(struct clic_opt *head);

clic_error clic_opt_find(struct clic_opt *head, const char *token, struct clic_opt **out);

void clic_opt_mark_provided(struct clic_opt* opt);

bool clic_opt_was_provided(struct clic_opt *opt);

#endif
