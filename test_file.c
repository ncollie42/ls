#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>

#define FLAG(x) flag[x - 'a']
char flag[20];

char **get_flags();

int main(int argc, char **argv)
{
    // flag[0] = 1;
    DIR *test;
    struct dirent *dirent;
    struct stat file_info;

    test = opendir(".");
    
    while ((dirent = readdir(test)))
    {
        if(FLAG('a'))
            printf("%s\n", dirent->d_name);
        else if (!(dirent->d_name[0] == '.'))
        {
            printf("name: %s\tino: %llu\ttype: %d\n", dirent->d_name, dirent->d_ino, dirent->d_type);
            lstat(dirent->d_name, &file_info);
            printf("%llu\n", file_info.st_ino);
        }
    }
}