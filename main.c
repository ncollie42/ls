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

fileInfo *makeInfoStruct(struct dirent *dirent)
{
    struct stat statInfo;
    struct passwd *pswd;
    struct group *grp;
    fileInfo *file;


    lstat(dirent->d_name, &statInfo);
    pswd = getpwuid(statInfo.st_uid);
    grp = getgrgid(statInfo.st_gid);

    file = malloc(sizeof(fileInfo));
    file->mode = statInfo.st_mode;
    file->nlink = statInfo.st_nlink;
    file->pname = pswd->pw_name;
    file->gname = grp->gr_name;
    file->size = statInfo.st_size;
    file->block = statInfo.st_blocks;
    file->time = ctime(&statInfo.st_mtimespec.tv_sec);
    file->seconds = statInfo.st_mtimespec.tv_sec;
    file->nano = statInfo.st_mtimespec.tv_nsec;
    file->name = strdup(dirent->d_name);
    return file;
}


t_list **readDir(char *dirname) {
    DIR             *dir;
    struct dirent   *dirent;
    t_list          **head;
    t_list          *node;

    head = makeListHead();  //Make func to make and set to NULL? *newHead
    dir = opendir(dirname);
    while ((dirent = readdir(dir)))
    {
        if (g_flag.a || dirent->d_name[0] != '.' )
        {
            node = newNode(makeInfoStruct(dirent));
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

void    walk(char *path)
{
    t_list **files;    
    t_list **queue;    

    files = readDir(path);
    queue = handleDir(files);
    
    if (g_flag.R)
        recurse(path, queue);
    lstdel(queue, delStrings);
}


int main(int argc, char **argv)
{
    argv = parseArgs(argv);
    setFunctions();

    walk(".");



    /*  print test function */
    // printFiles(files);
    // while(1);
    // sort(argv);
    // seperate_arguments splitArgs
    // printTrash()
    // printFiles()
    // hanldeDirs(dirs);
}