#include "header.h"

static void    move(char *dst, char *src)
{
    int n;

    n = -1;
    while (src[++n])
        dst[n] = src[n];
}

char    *joinPath(char *path, char *name)
{
    char    *new;
    int     size1;
    int     size2;
    int     total;

    if (!name)
        return NULL;
    if (!path)
        return strdup(name);
    size1 = nc_strlen(path);
    size2 = nc_strlen(name);
    total = size1 + size2;
    new = malloc(sizeof(char) * (total + 2));
    move(new, path);
    new[size1] = '/';
    move(&new[size1+1],name);
    new[total + 1] = '\0';
    return new;
}