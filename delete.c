#include "header.h"

void delStrings(void *str)
{
    free(str);
    str = NULL;
}

void delFieInfoStruct(void *tmp)
{
    fileInfo *file;

    file = tmp;
    free(file->pname);
    free(file->gname);
    free(file->name);
    free(file->time);
    free(file->path);
    free(file->link);
    free(file->mode);
    free(file);
    file = NULL;
}