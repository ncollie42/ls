#include "header.h"


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

    head = malloc(sizeof(char *));
    *head = NULL;
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


t_list **handleDir(t_list **files)
{
    int     total;
    t_list  *file;
    t_list  **strings;
    t_list  *node;
    total = 0;

    
    strings = malloc(sizeof(t_list *)); // Don't need?
    *strings = NULL;
    file = *files;//itter - make strings? iiter print?
    while(file)
    {
        total += ((fileInfo *)file->content)->block;
        node = newNode(makeFileString(file));
        append(strings, node);
        /* if recursive que que going -- return queue */
        file = file->next;
    }
    /* print dir */
    printDir(strings);
    /* free **files */
    return files;
}


int main(int argc, char **argv)
{
    argv = parseArgs(argv);
    setFunctions();

    t_list **files = readDir(".");
    t_list **queue = handleDir(files);

    // print test function 
    printFiles(files);

    // sort(argv);
    // seperate_arguments splitArgs
    // printTrash()
    // printFiles()
    // hanldeDirs(dirs);
    printf("%lu\n", sizeof(g_flag));
}