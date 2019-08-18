#include "header.h"

 void delStrings(void *str)
 {
     free(str);
     str = NULL;
 }

 void delFieInfoStruct(void *tmp)
 {
     fileInfo *file;

     file = tmp;
     free(file->pname);
     free(file->gname);
     free(file->name);
     free(file->time);
     free(file->path);
     if (file->link)
        free(file->link);
     free(file);
     file = NULL;
 }