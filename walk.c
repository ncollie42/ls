#include "header.h"

static t_list **readDir(char *path, char *name) {
    DIR             *dir;
    struct dirent   *dirent;
    t_list          **head;

    head = makeListHead();
    dir = opendir(path);
    if (!dir)
    {
        printf("ls: %s: Permission denied\n", name); 
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
    printf("\n%s:\n", GETPATH(curent));
    walk(curent);
}

void    startWalk(t_list **dirs)
{
    t_list *dir;

    dir = *dirs;
    if (dir)
    {
        if (HASNEXT(dir))
            printf("%s:\n", GETPATH(dir)); 
        walk(dir);
        if (HASNEXT(dir))
            lstIter(&dir->next, printNWalk);
    }
}

void    walk(t_list *curent)
{
    t_list **files;    
    t_list **queue;    

    files = readDir(GETPATH(curent), GETNAME(curent));
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