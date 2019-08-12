#include "header.h"

void    printFiles(t_list **head)
{
    int size = 0;
    t_list *tmp = *head;
    while(tmp)
    {
        fileInfo *file = tmp->content;

        printf("%d\t", file->mode);
        printf("%d\t", file->nlink);
        printf("%s\t", file->pname);
        printf("%s\t", file->gname);
        printf("%lld\t", file->size);
        printf("%s\t", file->name);
        printf("%s\t", file->time);
        size += file->block;
        tmp = tmp->next;
    }    
    printf("\ttotal: %d\n", size);
}