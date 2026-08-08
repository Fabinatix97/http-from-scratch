#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {

    pid_t p = fork();

    if(p<0) {
        perror("fork failed");
        return -1;
    }
    printf("Hello world!, process_id (pid) = %d\n", getpid());

    return 0;
}
