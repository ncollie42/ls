#include "header.h"

static t_list **readDir(char *path) {
    DIR             *dir;
    struct dirent   *dirent;
    t_list          **head;

    head = makeListHead();
    dir = opendir(path);
    if (!dir)
    {
        printf("ls: %s: Permission denied\n", path);
        return NULL;
    }
    while ((dirent = readdir(dir)))
    {
        if (g_flag.a || dirent->d_name[0] != '.' )
            addToListSorted(head, makeInfoStruct(path, dirent->d_name));
    }
    closedir(dir);
    return head;
}

static void    printNWalk(t_list *curent)
{
    printf("\n%s:\n", ((fileInfo *)curent->content)->path);
    walk(curent);
}

void    startWalk(t_list **dirs)
{
    t_list *dir;

    dir = *dirs;
    if (dir)
    {
        if (((fileInfo *)dir->next))
            printf("%s:\n", ((fileInfo *)dir->content)->path); 
        walk(dir);
        if ((fileInfo *)dir->next)
            lstIter(&dir->next, printNWalk);
    }
}

void    walk(t_list *curent)
{
    t_list **files;    
    t_list **queue;    

    files = readDir(((fileInfo *)curent->content)->path);   //Pass a pointer to the struct so i cant print name if it doesn't work.
    if (!files)
    {
        lstdel(files, delFieInfoStruct);
        return;
    }
    queue = handleDir(files);
    if (g_flag.R)
        lstIter(queue, printNWalk);
    lstdel(queue, delFieInfoStruct);
    lstdel(files, delFieInfoStruct);
}