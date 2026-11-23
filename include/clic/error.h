#ifndef ERROR_H
#define ERROR_H

typedef enum{
    CLIC_OK = 0,
    // Erros referentes às options
    CLIC_ERR_SHORT_INVALID_CHAR,
    CLIC_ERR_SHORT_TOO_LONG,

    CLIC_ERR_LONG_TOO_SHORT,
    CLIC_ERR_LONG_INVALID_CHAR,
    
    CLIC_ERR_INVALID_ARITY,

    // Erros do parser
    CLIC_ERR_DUPLICATE,
    CLIC_ERR_NOT_FOUND,

    CLIC_ERR_NOMEM
} clic_error;

const char *clic_error_string(clic_error e);

#endif
