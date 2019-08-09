#ifndef HEADER_H
#define HEADER_H
#include <stdio.h> // printf
#include <stdlib.h> // NULL
#include "nc_lib_buffer.h"

char                **parseArgs(char **args);
void                parseFlag(char *arg);
void                setFunctions(void);
seperated_arguments separateArgs(char **args);
void                (*getFileString)(void);

enum Bool{TRUE, FALSE};

typedef struct s_seperate_arguments
{
    dynamic_buffer *trash;
    dynamic_buffer *dirs;
    dynamic_buffer *files;
}seperated_arguments;

typedef struct s_flags
{
    int a:1;
    int l:1;
    int r:1;
    int t:1;
    int R:1;
}flags;

#endif