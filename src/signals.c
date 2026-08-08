#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_int_signal(int signum) {
    printf("\nReceived SIGINT");
    exit(signum);
}

void handle_other_signals(int signum) {
    printf("\nReceived signal: %d\n", signum);
    exit(signum);
}

int main() {
    signal(SIGINT, handle_int_signal);
    signal(SIGQUIT, handle_other_signals);
    signal(SIGABRT, handle_other_signals);
    signal(SIGFPE, handle_other_signals);

    for(int i = 0; i <= 2; i++) {
        printf("Hello world!\n");
        sleep(1);
    }

    raise(SIGFPE);
    //kill(getpid(), SIGKILL);

    return 0;
}
