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
void    printFile(t_list *curent)
{
    int size = 0;
    t_list *tmp = curent;
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

/* 
    Wrapper to add data to a list
    sorting with preset function
    *only to be used with fileInfo linked lists because of sort*
*/

void    addToListSorted(t_list **head, void *data)
{
    t_list *node;

    node = newNode(data);
    lstAddSorted(head, node, compare);
}