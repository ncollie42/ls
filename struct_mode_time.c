#include "header.h"

enum Color{RED, GREEN, YELLOW, BLUE, PURPLE, REG};
char *colors[] = {"\033[0;31m", "\033[0;32m", "\033[1;33m", "\033[0;34m",  "\033[0;35m", "\033[0m"};

void setModeNColor(char *mode, char c, char **color, int index)
{
	mode[0] = c;
	*color = colors[index];
}

static void    set_type(char *mode, int num, char **color)
{
    if (S_ISREG(num))
        setModeNColor(mode, '-', color, (mode[3] == 'x') ? RED : REG);
	else if (S_ISDIR(num))
        setModeNColor(mode, 'd', color, BLUE);
	else if (S_ISBLK(num))
        setModeNColor(mode, 'b', color, GREEN);
	else if (S_ISCHR(num))
        setModeNColor(mode, 'c', color, YELLOW);
	else if (S_ISLNK(num))
        setModeNColor(mode, 'l', color, PURPLE);
	else if (S_ISSOCK(num))
        setModeNColor(mode, 's', color, REG);
	else if (S_ISFIFO(num))
        setModeNColor(mode, 'P', color, REG);
}

static void    set_mode(char *mode, int num, char **color)
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

char    *mode(int num, char **color) 
{
    char    *mode;
    int     n;
    
    n = 0;
    if (!(mode = malloc(sizeof(char) * 11)))
		return (NULL);
    set_mode(mode, num, color);
    set_type(mode, num, color);
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