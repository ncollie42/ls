#include "header.h"
#include <stdio.h>
#define BUFF_SIZE 500 // Should be big enough

char    *fileLongMake(t_list *file)
{
    char *buffer;
	fileInfo *f;

	buffer = nc_malloc(BUFF_SIZE);	
	f = file->content;
	sprintf(buffer, "%d  %2d %5s %5s %lld %s %s %s",
		f->mode,
		f->nlink,
		f->pname,
		f->gname,
		f->size,
		f->time,
		f->name,
		"link");
    return buffer;
}

char    *fileShortMake(t_list *file)
{
	char *buffer;

	buffer = nc_malloc(BUFF_SIZE);
    sprintf(buffer, "%s", ((char *)((fileInfo *)file->content)->name));
	return buffer;
}

void    printLong(t_list **files)
{
	t_list *file;

	file = *files;
	while(file)
	{
		printf("%s\n", ((char *)file->content));
		file = file->next;
	}
}

void    printShort(t_list **files)
{
	t_list *file;

	file = *files;
	while(file)
	{
		printf("%s\n", ((char *)file->content));
		file = file->next;
	}	
}