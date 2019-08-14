#include "header.h"
#define ISDIR(x) S_ISDIR(((fileInfo *)(x)->content)->mode)

#define GETBLOCKS(x) ((fileInfo *)(x)->content)->block
#define GETNAME(x) ((fileInfo *)(x)->content)->name

extern flags g_flag;

void    setFunctions(void)
{
    if (g_flag.l) {
        makeFileString = fileLongMake;
        printDir = printLong; 
    } else {
        makeFileString = fileShortMake;
        printDir = printShort;
    }
    if (g_flag.r)
    {
        if (g_flag.t)
            compare = byTimeRev;
        else
            compare = byNameRev;
    }
    else if (g_flag.t)
        compare = byTime;
    else
        compare = byName;
}

fileInfo *makeInfoStruct(char *path, char *name)
{
    struct stat statInfo;
    struct passwd *pswd;
    struct group *grp;
    fileInfo *file;

    file = malloc(sizeof(fileInfo));
    file->path = joinPath(path, name); //if g_flag l -> do all
    file->link = getLink(file->path);
    lstat(file->path, &statInfo);
    pswd = getpwuid(statInfo.st_uid);
    grp = getgrgid(statInfo.st_gid);
    file->mode = statInfo.st_mode;  //function to make proper str
    file->nlink = statInfo.st_nlink;
    file->pname = strdup(pswd->pw_name);
    file->gname = strdup(grp->gr_name);
    file->size = statInfo.st_size;
    file->block = statInfo.st_blocks;
    file->time = ctime(&statInfo.st_mtimespec.tv_sec); // function to make proper str
    file->seconds = statInfo.st_mtimespec.tv_sec;
    file->nano = statInfo.st_mtimespec.tv_nsec;
    file->name = strdup(name);
    return file;
}


t_list **readDir(char *path) {
    DIR             *dir;
    struct dirent   *dirent;
    t_list          **head;
    t_list          *node;

    head = makeListHead();  //Make func to make and set to NULL? *newHead
    dir = opendir(path);
    while ((dirent = readdir(dir)))
    {
        if (g_flag.a || dirent->d_name[0] != '.' )
        {
            node = newNode(makeInfoStruct(path, dirent->d_name));
            lstAddSorted(head, node, compare);
        }
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
            append(queue, newNode(strdup((GETNAME(file)))));
        file = file->next;
    }
    printDir(strings);
    lstdel(strings, delStrings);
    return queue;
}



void    recurse(char *curentPath, t_list **dirName)
{
    t_list  *curent;
    char    *newPath;

    curent = *dirName;
    while (curent)
    {
        newPath = joinPath(curentPath, (char *)curent->content);
        printf("\n%s:\n", newPath);
        walk(newPath);
        free(newPath);
        curent = curent->next;
    }
}

void    walk(char *path)    //t_list *struct ?
{
    t_list **files;    
    t_list **queue;    

    files = readDir(path);
    queue = handleDir(files);   // returns struct and not string
    
    if (g_flag.R)
        recurse(path, queue);   // pass struct and not queue + path
    lstdel(queue, delStrings);  // lstdel files? That also include Queue ?
}

void    startWalk(t_list **dirs)
{
    // walk()
    lstIter(dirs, printFile);
}

static void     initArgsStruct(seperated_arguments *tmp)
{
    tmp->trash = makeListHead();
    tmp->files = makeListHead();
    tmp->dirs = makeListHead();
}

seperated_arguments seperateArgs(char **argv)
{
    seperated_arguments splitArgs;
    int                 n;
    struct stat         statInfo;

    n = -1;
    initArgsStruct(&splitArgs);
    while(argv[++n])
    {
       if ((lstat(argv[n], &statInfo)) < 0)
            lstAddSorted(splitArgs.trash, newNode(strdup(argv[n])), stringByName);
       else if (S_ISDIR(statInfo.st_mode))
            addToListSorted(splitArgs.dirs, makeInfoStruct(NULL, argv[n]));
       else
            addToListSorted(splitArgs.files, makeInfoStruct(NULL, argv[n]));
    }
    return splitArgs;
}

int main(int argc, char **argv)
{
    t_list  **sortedArgs;
    seperated_arguments splitArgs;

    argv = parseArgs(argv);
    setFunctions();

    splitArgs = seperateArgs(argv);

    // sortedArgs = sortArgs(argv); // Sort when seperate?? don't need this
    // printShort(splitArgs.trash);
    startWalk(splitArgs.dirs); // Don't Need this? just iter on main?
    //convert arv into sorted linked list
    // pass list to seperate lists
    // print trash, reg, then startWalk();

    // startWalk();
    // walk("."); //with a struct info

}