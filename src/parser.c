#include <stdlib.h>
#include <string.h>

#include "clic/parser.h"
#include "clic/error.h"
#include "clic/opt.h"

typedef enum {
    PARSE_SEEK,     // lendo comandos ou opções
    PARSE_ARGS,     // Lendo argumentos de um comando ou opção
    PARSE_ENDED     // Quando o usuário digita "--". Tudo vira argumento posicional
} parse_mode;

struct clic_parser
{
    struct clic_opt *options;
    size_t  option_count;
};

struct clic_parser *clic_parser_init(void)
{
    struct clic_parser *p = malloc(sizeof(struct clic_parser));
    
    p->options = NULL;
    p->option_count = 0;

    return p;
}

void clic_parser_free(clic_parser *parser)
{
    clic_opt_free_all(parser->options);
    free(parser);
}

clic_error clic_parse(struct clic_parser *parser,int argc, char *argv[]){
    parse_mode mode = PARSE_SEEK;
    clic_error curr_err;
    struct clic_opt *curr_opt;

    // Ignora o comando inicial
    argv++; 
    argc--;

    for(int i = 0; i < argc; i++){
        char *token = argv[i];

        if(mode == PARSE_SEEK)
        {
            curr_err = clic_opt_find(parser->options, token, &curr_opt);
            if(curr_err != CLIC_OK) return curr_err;
            
            clic_opt_mark_provided(curr_opt);
            mode = PARSE_SEEK;
        }

        if(mode == PARSE_ARGS)
        {
            if(curr_opt != NULL)
                return CLIC_OK;
        }
    }
}
