#ifndef PARSER_H
#define PARSER_H

#include "clic/error.h"
#include "clic/opt.h"

typedef struct clic_parser clic_parser;

struct clic_parser *clic_parser_init(void);
void clic_parser_free(clic_parser *parser);

clic_error clic_parse(struct clic_parser *parser, int argc, char *argv[]);

clic_error clic_parser_add_option(clic_opt *option);

#endif
