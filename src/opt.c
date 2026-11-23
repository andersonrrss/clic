#include <stddef.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "clic/arity.h"
#include "clic/opt.h"
#include "clic/error.h"

struct clic_opt
{
    char short_name;
    const char *long_name;
    const char *description;
    int argc;
    char **argv;
    bool was_provided;
    bool required;
    clic_value_arity arity;
    opt_action_fn opt_action;
    clic_opt *next;
};

// ###########################################
// ============ HELPERS PRIVADOS =============
// ###########################################

static clic_error normalize_short(const char *s, char *out)
{
    const char *p = s;
    if(*p == '-') p++;

    if(strlen(p) != 1) return CLIC_ERR_SHORT_TOO_LONG;
    
    if(isalpha((unsigned char)*p)) return CLIC_ERR_SHORT_INVALID_CHAR; 
    
    *out = *p;
    return CLIC_OK;
}

static clic_error normalize_long(const char *s, const char **out)
{
    const char *p = s;
    if(strncmp(p, "--", 2) == 0)
        p += 2;

    size_t len = strlen(p);
    if(len < 1) return CLIC_ERR_LONG_TOO_SHORT;
    
    if(!isalnum((unsigned char)p[0])) 
        return CLIC_ERR_LONG_INVALID_CHAR;
    
    for(size_t i = 1; i < len - 1; i++)
    {
        unsigned char c = (unsigned char) p[i];
        if(isspace(c)) return CLIC_ERR_LONG_INVALID_CHAR;
        if(!isalnum(c) && !strchr("-_.", c)) return CLIC_ERR_LONG_INVALID_CHAR;
    }

    if(len > 1 && !isalnum((unsigned char)p[len - 1])) 
        return CLIC_ERR_LONG_INVALID_CHAR;
    
    *out = p;

    return CLIC_OK;
}

static struct clic_opt *find_short(struct clic_opt *head, char c)
{
    for(struct clic_opt *curr = head; curr != NULL; curr = curr->next)
    {
        if(curr->short_name == c)
            return curr;
    }
    
    return NULL;
}

static struct clic_opt *find_long(struct clic_opt *head, const char *name)
{
    for(struct clic_opt *curr = head; curr != NULL; curr = curr->next)
    {
        if(strcmp(curr->long_name, name) == 0) 
            return curr;
    }

    return NULL;
}

// ###########################################
// ============   API PÚBLICA   =============
// ###########################################

clic_error clic_opt_new(struct clic_opt **out, const char *raw_short, const char *raw_long, const char *description, clic_value_arity arity, opt_action_fn action, bool required){
    struct clic_opt *opt = malloc(sizeof(struct clic_opt));

    char short_norm;
    const char *long_norm;

    clic_error e;
    // permite que o usuário digite "-v" ou "v" na definição da option
    e = normalize_short(raw_short, &short_norm);
    if(e != CLIC_OK)
    {
        free(opt);
        return e;
    }

    e = normalize_long(raw_long, &long_norm);
    if(e != CLIC_OK)
    {   
        free(opt);
        return e;
    }

    opt->short_name = short_norm;
    opt->long_name = long_norm;
    opt->description = description;
    opt->opt_action = action;
    opt->arity = arity;
    opt->required = required;
    opt->next = NULL;
    opt->was_provided = false;
    
    (*out) = opt;

    return CLIC_OK;
}

clic_error clic_opt_find(struct clic_opt *head, const char *token, struct clic_opt **out)
{
    *out = NULL;
    
    if(strncmp(token, "--", 2) == 0)
    {
        const char *name;
        clic_error err = normalize_long(token, &name);
        if(err != CLIC_OK) return err;

        *out = find_long(head, name);
    }
    else 
    {
        char c;
        clic_error err = normalize_short(token, &c);
        if(err != CLIC_OK) return err;
        
        *out = find_short(head, c);
    }

    return *out ? CLIC_OK : CLIC_ERR_NOT_FOUND;
}

void clic_opt_free_all(struct clic_opt *head)
{
    struct clic_opt *curr = head;
    struct clic_opt *next = NULL;
    while(curr != NULL)
    {
        next = curr->next;
        free(curr);
        curr = next;
    }
}

void clic_opt_mark_provided(struct clic_opt* opt)
{
    if(opt != NULL)
        opt->was_provided = true;
}

bool clic_opt_was_provided(struct clic_opt *opt)
{
    return opt != NULL && opt->was_provided;
}
