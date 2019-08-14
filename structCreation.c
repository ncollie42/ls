#include "header.h"

char *getLink(char *path)
{
    int     size;
    char    buff[PATH_MAX + 1];

    size = readlink(path, buff, PATH_MAX);
    if (size < 0)
        return nc_malloc(sizeof(char));
    buff[size] = '\0';
    if (size == PATH_MAX)
        printf("Path of link might have been truncated\n");
    return nc_strjoin("-> ", buff);
}