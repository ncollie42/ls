#ifndef HEADER_H
#define HEADER_H
#include <stdio.h> // printf
#include <stdlib.h> // NULL
// #include "nc_lib_buffer.h"
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/xattr.h>
#include <strings.h>
# include <sys/ioctl.h>
#include <unistd.h> // getuid
#include "nc_lib.h"

typedef struct s_seperate_arguments
{
    t_list *trash;
    t_list *dirs;
    t_list *files;
}seperated_arguments;

typedef struct s_info
{
    int mode;
    int nlink;
    char *pname;
    char *gname;
    long long int size;
    long long int block;
    char *name;
    char *time;
    long seconds;
    int nano;
}fileInfo;

void                setFunctions(void);
seperated_arguments separateArgs(char **args);

/* file Strings Make && print */

char    *fileLongMake(t_list *file);
char    *fileShortMake(t_list *file);
char    *(*makeFileString)(t_list *file);
void    printLong(t_list **files);
void    printShort(t_list **files);
void    (*printDir)(t_list **strings);

/* Sorting */

int     byName(void *one, void *two);
int     byNameRev(void *one, void *two);
int     byTime(void *one, void *two);
int     byTimeRev(void *one, void *two);
int     (*compare)(void*,void*);

/* flags */

char **parseArgs(char **args);
typedef struct s_flags
{
    int a:1;
    int l:1;
    int r:1;
    int t:1;
    int R:1;
}flags;
enum Bool{FLASE, TRUE};

flags g_flag;

/* Test */
void printFiles(t_list **head);

#endif