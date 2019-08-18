#include "header.h"

#define ISDIR(x) S_ISDIR(((fileInfo *)(x)->content)->mode)
#define GETBLOCKS(x) ((fileInfo *)(x)->content)->block
#define GETNAME(x) ((fileInfo *)(x)->content)->name

extern flags g_flag;

t_list **readDir(char *path) {
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

static int isDots(t_list *file)
{
    char *name;

    name = ((fileInfo *)file->content)->name;
    if (!strcmp(name, ".") || !strcmp(name, ".."))
        return TRUE;
    return FALSE;
}

/* 
    Arg: list of files for curent directory
    return: if recursive, a queue of directory
*/

void    handleFiles(t_list **files)
{
    t_list      **strings;
    t_list      *file;

    strings = makeListHead(); 
    file = *files;
    while(file)
    {
        append(strings, newNode(makeFileString(file)));
        file = file->next; 
    }
    print(strings);
    lstdel(strings, delStrings);
}

t_list **handleDir(t_list **files)
{
    int         total;
    t_list      *file;
    t_list      **strings;
    t_list      **queue;

    total = 0;
    strings = makeListHead();
    queue = makeListHead();
    file = *files;
    while(file)
    {
        total += GETBLOCKS(file);
        append(strings, newNode(makeFileString(file)));
        if (g_flag.R && ISDIR(file) && !isDots(file))
            append(queue, newNode(copyFileInfoStruct((fileInfo *)file->content)));
        file = file->next;
    }
    if (g_flag.l)
        printf("total %d\n", total);
    print(strings);
    lstdel(strings, delStrings);
    return queue;
}

void    printNWalk(t_list *curent)
{
    printf("\n%s:\n", ((fileInfo *)curent->content)->path);
    walk(curent);
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

void    startWalk(t_list **dirs)
{
    t_list *dir;

    dir = *dirs;
    if (dir)
    {
        if (((fileInfo *)dir->next))
            printf("%s:\n", ((fileInfo *)dir->content)->path);  // if file skip a line, if 2+dirs print then skip lines or add line at end of file
        walk(dir);
        if ((fileInfo *)dir->next)
            lstIter(&dir->next, printNWalk);
    }
}

int main(int argc, char **argv)
{
    t_list  **sortedArgs;
    seperated_arguments splitArgs;

    argv = parseArgs(argv);
    setFunctions();
    splitArgs = separateArgs(argv);
    printTrash(splitArgs.trash);
    handleFiles((splitArgs.files));
    if (*splitArgs.files && *splitArgs.dirs)
        printf("\n");
    startWalk(splitArgs.dirs);
}

/*
    Todo:
        printing files as itter ? on buffer? faster?

        print reg
        Mode functions
        time trim functions
*/