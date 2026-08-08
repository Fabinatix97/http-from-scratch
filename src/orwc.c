#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

// Just some practicing of open, read, write, and close

int main() {

    char path[] = "src/test.txt";
    printf("file path: %s\n\n", path);

    printf("opening file...\n\n");
    int fd = open(path, O_RDONLY);
    printf("file descriptor: %d\n\n", fd);
    printf("error number: %d\n\n", errno);

    printf("reading file...\n\n");
    char buf[10];
    size_t nbytes;
    nbytes = sizeof(buf);
    ssize_t bytes_read = read(fd, buf, nbytes);
    printf("bytes read: %zu\n\n", bytes_read);
    printf("error number: %d\n\n", errno);

    printf("trying to open the same file for writing...\n\n");
    open(path, O_RDONLY);
    printf("error number: %d\n\n", errno);

    printf("closing file...\n\n");
    int close_status = close(fd);
    printf("close status: %d\n\n", close_status);

    printf("opening, writing and closing a new file...\n\n");
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    int fd3 = open("src/newfile", O_WRONLY | O_CREAT, mode);
    ssize_t bytes_written = write(fd3, "Hello World\n", strlen("Hello World\n"));
    printf("bytes written: %zu\n\n", bytes_written);
    fsync(fd3);
    close(fd3);
    printf("done.\n\n");

    return 0;
}
