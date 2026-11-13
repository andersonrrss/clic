#ifndef PARSER_H
#define PARSE_H

typedef enum {
    PARSE_SEEK,     // lendo comandos ou opções
    PARSE_ARGS,     // Lendo argumentos de um comando ou opção
    PARSE_ENDED     // Quando o usuário digita "--". Tudo vira argumento posicional
} parse_mode;

int parse_cli(int argc, char *argv[]);

#endif