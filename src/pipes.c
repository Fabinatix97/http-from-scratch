#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int pipefd[2];
    char buf;
    pid_t cpid;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (pipe(pipefd) == -1) {
        err(EXIT_FAILURE, "pipe");
    }

    printf("read end of the pipe (pipefd[0]): %d\n", pipefd[0]);
    printf("write end of the pipe (pipefd[1]): %d\n", pipefd[1]);

    cpid = fork();
    if (cpid == -1) {
        err(EXIT_FAILURE, "fork");
    }

    if (cpid == 0) {    // this is the child which will read only
        close(pipefd[1]);
        while (read(pipefd[0], &buf, 1) > 0) {
            write(STDOUT_FILENO, &buf, 1);
            write(STDOUT_FILENO, "\n", 1);
        }
        write(STDOUT_FILENO, "\n", 1);
        close(pipefd[-1]);
        exit(EXIT_SUCCESS);
    } else {            // this is the parent which will write only
        close(pipefd[0]);
        write(pipefd[1], argv[1], strlen(argv[1]));
        close(pipefd[1]);
        wait(NULL);
        exit(EXIT_SUCCESS);
    }

    return 0;
}
