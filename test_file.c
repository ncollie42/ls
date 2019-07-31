#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/xattr.h>
#include <strings.h>
#include <unistd.h> // getuid
#define FLAG(x) flag[x - 'a']
char flag[20];

char **get_flags();

int main(int argc, char **argv)
{
    // flag[0] = 1;
    DIR *test;
    struct dirent *dirent;
    struct stat fileInfo;
    struct passwd *pswd;
    struct group *grp;

    test = opendir(".");
    
    char *pname;
    char *gname;
    char *time1;
    pswd = getpwuid(getuid());
    grp = getgrgid(getgid());

    pname = pswd->pw_name;
    gname = grp->gr_name;
    time_t current_time = time(NULL);
    char    atributes[100];
    bzero(atributes, 100);
    
    // xattr -w nico best a -- xattr -w haha best a
    int x = listxattr("/tmp/a", atributes, 100, XATTR_NOFOLLOW);
    printf("%d %s %s\n",x, atributes, atributes + 5);

    

    printf("NOW TIME:\t%s", ctime(&current_time));
    printf("Mode\t\t\n");
    while ((dirent = readdir(test)))
    {
        if(FLAG('a'))
            printf("%s\n", dirent->d_name);
        else if (!(dirent->d_name[0] == '.'))
        {
            lstat(dirent->d_name, &fileInfo);
            printf("%d\t", fileInfo.st_mode);
            printf("%d\t", fileInfo.st_nlink);
            printf("%s\t", pname);
            printf("%s\t", gname);
            printf("%lld\t", fileInfo.st_size);
            // printf("%d\t", fileInfo.st_blksize);
            printf("%lld\t", fileInfo.st_blocks);
            time1 = ctime(&fileInfo.st_mtimespec.tv_sec);
            printf("%s\t\n", time1);
            pswd = getpwuid(fileInfo.st_uid);
            // printf("%d\n", pswd. );


            // printf("name: %s\tino: %llu\ttype: %d ", dirent->d_name, dirent->d_ino, dirent->d_type);
            // printf("ino %llu\n", fileInfo.st_ino);
        }
    }

}