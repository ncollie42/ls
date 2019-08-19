#include "header.h"

static void    set_type(char *mode, int num)
{
    if (S_ISREG(num))
        mode[0] = '-';
	else if (S_ISDIR(num))
		mode[0] = 'd';
	else if (S_ISBLK(num))
		mode[0] = 'b';
	else if (S_ISCHR(num))
		mode[0] = 'c';
	else if (S_ISLNK(num))
		mode[0] = 'l';
	else if (S_ISSOCK(num))
		mode[0] = 's';
	else if (S_ISFIFO(num))
		mode[0] = 'P';
}

static void    set_mode(char *mode, int num)
{
    int n;

    n = 1;
	mode[n++] = (num & S_IRUSR) ? 'r' : '-';
	mode[n++] = (num & S_IWUSR) ? 'w' : '-';
	mode[n++] = (num & S_IXUSR) ? 'x' : '-';
	mode[n++] = (num & S_IRGRP) ? 'r' : '-';
	mode[n++] = (num & S_IWGRP) ? 'w' : '-';
	mode[n++] = (num & S_IXGRP) ? 'x' : '-';
	mode[n++] = (num & S_IROTH) ? 'r' : '-';
	mode[n++] = (num & S_IWOTH) ? 'w' : '-';
	mode[n++] = (num & S_IXOTH) ? 'x' : '-';
}

static void    extra_modes(char *mode, int num)
{
	if (num & S_ISUID)
		mode[3] = (mode[3] == '-') ? 'S' : 's';
	if (num & S_ISGID)
		mode[6] = (mode[6] == '-') ? 'S' : 's';
	if (num & S_ISVTX)
		mode[9] = (mode[9] == '-') ? 'T' : 't';
}

char    *mode(int num) {
    char    *mode;
    int     n;
    
    n = 0;
    if (!(mode = malloc(sizeof(char) * 11)))
		return (NULL);
    set_type(mode, num);
    set_mode(mode, num);
    extra_modes(mode, num);
    //Add extended @ + here
    mode[10] = '\0';
    return mode;
}


char	*trimTime(char *ctime, long seconds)
{
	char *new;

	if ((new = malloc(sizeof(char) * 13)) == NULL)
		return (NULL);
	new[12] = '\0';
	if ((time(NULL) - seconds) > 15780000)
	{
		nc_strncpy(new, (ctime + 4), 7);
		nc_strncpy((new + 7), (ctime + 19), 5);
	}
	else
		nc_strncpy(new, (ctime + 4), 12);
	return (new);
}