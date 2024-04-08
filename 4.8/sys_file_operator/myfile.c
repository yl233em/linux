#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
    int fd = open("./demo", O_CREAT | O_TRUNC | O_WRONLY, 0666);
    const char* s = "i like linux!\n";
    write(fd, s, strlen(s));
    close(fd);

    return 0;
}