#ifndef HEADER_H
#define HEADER_H
#include <stdio.h> // printf
#include <stdlib.h> 
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/xattr.h>
#include <strings.h>
# include <sys/ioctl.h>
#include <unistd.h> 
#include "nc_lib.h"

enum Bool{FALSE, TRUE};
#define PATH_MAX        4096
#define RESET   "\033[0m"
#define ISDIR(x) ((((fileInfo *)(x)->content)->mode)[0] == 'd')
#define GETBLOCKS(x) ((fileInfo *)(x)->content)->block
#define GETPATH(x) ((fileInfo *)(x)->content)->path
#define GETNAME(x) ((fileInfo *)(x)->content)->name
#define HASNEXT(x) ((fileInfo *)(x)->next)

    /* flags */

typedef struct s_flags
{
    int a:1;
    int l:1;
    int r:1;
    int t:1;
    int R:1;
}flags;

flags g_flag;

    /* to split arguments on main */

typedef struct s_seperate_arguments
{
    t_list **trash;
    t_list **dirs;
    t_list **files;
}seperated_arguments;

    /* FileInfo struct */

typedef struct s_info
{
    char            *mode;
    char            *pname;
    char            *gname;
    char            *name;
    char            *time;
    char            *path;
    char            *link;
    long long int   size;
    long long int   block;
    int             nlink;
    long            seconds;
    long            nano;
    char            *color;
}fileInfo;


/* strings */

char    *(*makeFileString)(t_list *file);
char    *fileLongMake(t_list *file);
char    *fileShortMake(t_list *file);
void    print(t_list **files);
void    printTrash(t_list **files);

/* Sorting */

int     byName(void *one, void *two);
int     byNameRev(void *one, void *two);
int     byTime(void *one, void *two);
int     byTimeRev(void *one, void *two);
int     stringByName(void *one, void *two);
int     (*compare)(void*,void*);



/* deleting */

void        delStrings(void *str);
void        delFieInfoStruct(void *file);

/* Struct Info creation */

char *getLink(char *path);

/* fileINfo Struct creation */

void        *copyFileInfoStruct(fileInfo *old);
fileInfo    *makeInfoStruct(char *path, char *name);
        
        /* mode & time */

char	*trimTime(char *ctime, long seconds);
char    *mode(int num, char **color);

        /* path */

char        *joinPath(char *s1, char *s2);

/* Walk */

void    startWalk(t_list **curent);
void    walk(t_list *curent);


/* init */

char                **parseArgs(char **args);
void                setFunctions(void);
seperated_arguments separateArgs(char **argv);

/* main */

t_list **handleDir(t_list **files);

/* wrapper */

void    addToListSorted(t_list **head, void *data);

#endif