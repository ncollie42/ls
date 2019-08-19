#include "header.h"

#define ISDIR(x) ((((fileInfo *)(x)->content)->mode)[0] == 'd')
#define GETBLOCKS(x) ((fileInfo *)(x)->content)->block
#define GETNAME(x) ((fileInfo *)(x)->content)->name

extern flags g_flag;

/* 
    A wrapper to lstAddSorted using the compare function 
    +Only use with fileInfo linked-list+
*/
void    addToListSorted(t_list **head, void *data)
{
    t_list *node;

    node = newNode(data);
    lstAddSorted(head, node, compare);
}

static int isDots(t_list *file)
{
    char *name;

    name = ((fileInfo *)file->content)->name;
    if (!strcmp(name, ".") || !strcmp(name, ".."))
        return TRUE;
    return FALSE;
}

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
        print reg
*/