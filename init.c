#include "header.h"

#define FLAGUSAGE  "usage: ls [-atlrR] [file ...]"
extern flags g_flag;


void    setFunctions(void)
{
    makeFileString = (g_flag.l) ? fileLongMake : fileShortMake;
    if (g_flag.r && g_flag.t)  // Dispatch table for functions?
        compare = byTimeRev;
    else if (g_flag.r)
        compare = byNameRev;
    else if (g_flag.t)
        compare = byTime;
    else
        compare = byName;
}


static void    parseFlag(char *arg)
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
    return args;
}


static void     initArgsStruct(seperated_arguments *tmp)
{
    tmp->trash = makeListHead();
    tmp->files = makeListHead();
    tmp->dirs = makeListHead();
}

seperated_arguments separateArgs(char **argv)
{
    seperated_arguments splitArgs;
    struct stat         statInfo;

    initArgsStruct(&splitArgs);
    while(*argv)
    {
       if ((lstat(*argv, &statInfo)) < 0)
            lstAddSorted(splitArgs.trash, newNode(strdup(*argv)), stringByName);
       else if (S_ISDIR(statInfo.st_mode))
            addToListSorted(splitArgs.dirs, makeInfoStruct(NULL, *argv));
       else
            addToListSorted(splitArgs.files, makeInfoStruct(NULL, *argv));
        argv++;
    }
    return splitArgs;
}