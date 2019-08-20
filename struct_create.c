#include "header.h"

void    *copyFileInfoStruct(fileInfo *old)
{
    fileInfo *file;

    file = malloc(sizeof(fileInfo));
    file->path = strdup(old->path);
    file->link = strdup(old->link);
    file->mode = strdup(old->mode);
    file->nlink = old->nlink;
    file->pname = strdup(old->pname);
    file->gname = strdup(old->gname);
    file->size = old->size;
    file->block = old->block;
    file->time = strdup(old->time);
    file->seconds = old->seconds;
    file->nano = old->nano;
    file->name = strdup(old->name);

    return file;
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
    file->mode = mode(statInfo.st_mode, &file->color);
    file->nlink = statInfo.st_nlink;
    file->pname = strdup(pswd->pw_name);
    file->gname = strdup(grp->gr_name);
    file->size = statInfo.st_size;
    file->block = statInfo.st_blocks;
    file->seconds = statInfo.st_mtimespec.tv_sec;
    file->nano = statInfo.st_mtimespec.tv_nsec;
    file->time = trimTime(ctime(&statInfo.st_mtimespec.tv_sec), file->seconds);
    file->name = strdup(name);
    return file;
}