#include "header.h"
#include "nc_lib.h"
#define FLAGUSAGE  "usage: ls [-atlrR] [file ...]"
flags g_flag;


void    setFunction(void)
{
    // if (g_flag.l) {

    // } else {

    // }
    // if (g_flag.r)
}

void    parseFlag(char *arg)
{
    int n;
    
    n = 0;
    while(arg[++n])
    {
        if (arg[n] == 'a')
            g_flag.a = TRUE;
        else if (arg[n] == 't')
            g_flag.t = TRUE;
        else if (arg[n] == 'r')
            g_flag.r = TRUE;
        else if (arg[n] == 'R')
            g_flag.R = TRUE;
        else if (arg[n] == 'l')
            g_flag.l = TRUE;
        else {
            printf("ls: illegal option -- %c\n%s", arg[n], FLAGUSAGE);
            exit(EXIT_FAILURE);
        } 
    }
}

char **parseArgs(char **args)
{
    int n;

    n = 0;
    while(args[++n])
    {
        if (args[n][0] == '-' && nc_strlen(args[n]) > 1)
            parseFlag(args[n]);
        else
            return(&args[n]);
    }
    args[0][0] = '.';
    args[0][1] = '\0';
    args[1] = NULL;
    return NULL;
}

int main(int argc, char **argv)
{
    argv = parseArgs(argv);

    // setFunctions();
    // sort(argv);
    // seperate_arguments splitArgs
    // printTrash()
    // printFiles()
    // hanldeDirs(dirs);
    printf("%lu\n", sizeof(g_flag));
}