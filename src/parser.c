#include <string.h>

#include "parser.h"
#include "internal.h"

int parse_cli(int argc, char *argv[]){
    parse_mode mode = PARSE_SEEK;
    clic_argument *value;

    clic_option option;

    // Ignora o comando inicial
    argv++; 
    argc--;

    for(int i = 0; i < argc; i++){
        char *token = argv[i];

        if(PARSE_SEEK)
        {
            if(strncmp(token, "--", 2))
            {
                
            }
        }
    }
}