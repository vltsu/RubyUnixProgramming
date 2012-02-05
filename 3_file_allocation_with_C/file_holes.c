#include <stdio.h>
#include <fcntl.h>

int main(char * filename, int filesize)
{
    int fd;
    fd = open("write_here.txt", O_APPEND | O_WRONLY | O_CREAT | O_TRUNC,
               S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
               S_IROTH | S_IWOTH);


    posix_fallocate(fd, 0, 1048576);

    close(fd);
}
