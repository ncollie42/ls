#include "header.h"

int byName(void *one, void *two)
{
    fileInfo *a;
    fileInfo *b;
    
    a = (fileInfo *)((t_list *)one)->content;
    b = (fileInfo *)((t_list *)two)->content;
    return strcmp(a->name, b->name);
}

int byNameRev(void *one, void *two)
{
    fileInfo *a;
    fileInfo *b;
    
    a = (fileInfo *)((t_list *)one)->content;
    b = (fileInfo *)((t_list *)two)->content;
    return strcmp(b->name, a->name);
}

int byTime(void *one, void *two)
{
    fileInfo *a;
    fileInfo *b;
    long dif;

    a = (fileInfo *)((t_list *)one)->content;
    b = (fileInfo *)((t_list *)two)->content;

    dif = (b->seconds - a->seconds);
    return (dif == 0) ? (b->nano - a->nano) : (int)dif;
}

int byTimeRev(void *one, void *two)
{
    fileInfo *a;
    fileInfo *b;
    long dif;

    a = (fileInfo *)((t_list *)one)->content;
    b = (fileInfo *)((t_list *)two)->content;

    dif = (a->seconds - b->seconds);
    return (dif == 0) ? (a->nano - b->nano) : (int)dif;
}