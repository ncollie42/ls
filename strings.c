#include "header.h"
#include <stdio.h>

#define BUFF_SIZE 500 // Should be big enough

char    *fileLongMake(t_list *file)
{
    char *buffer;
	fileInfo *f;

	buffer = nc_malloc(BUFF_SIZE);	
	f = file->content;
	sprintf(buffer, "%s  %2d %5s %5s %lld %s %s%s%s %s",
		f->mode,
		f->nlink,
		f->pname,
		f->gname,
		f->size,
		f->time,
		f->color, f->name, RESET,
		f->link);
    return buffer;
}

char    *fileShortMake(t_list *file)
{
	char *buffer;
	fileInfo *f;

	f = file->content;
	buffer = nc_malloc(BUFF_SIZE);
    sprintf(buffer, "%s%s%s", f->color, f->name, RESET);
	return buffer;
}

void    print(t_list **files)
{
	t_list *file;

	file = *files;
	while(file)
	{
		printf("%s\n", ((char *)file->content));
		file = file->next;
	}	
}


void    printTrash(t_list **files)
{
	t_list *file;

	file = *files;
	while(file)
	{
		printf("ls: %s: No such file or directory\n", ((char *)file->content));
		file = file->next;
	}	
}