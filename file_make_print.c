#include "header.h"

char    *fileLongMake(t_list *file)
{
    char *tmp;
	// tmp = Sprintf("%s  %2d %5s %5s %6d %s %s %s",
	// 	file.Mode(),
	// 	stat.Nlink,
	// 	user,
	// 	group,
	// 	stat.Size,
	// 	file.ModTime().Format("Jan _2 15:04"),
	// 	file.Name(),
	// 	link)
    return tmp;
}

char    *fileShortMake(t_list *file)
{
	char *buffer;

	buffer = malloc(sizeof(char) * 255);//change size
	memset(buffer, '\0', 255);
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