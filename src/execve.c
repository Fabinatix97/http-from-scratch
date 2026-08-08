#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    printf("Hello from the main program!\n");
    printf("Calling a new program...\n");

    //printf("argc: %d\n", argc);
    //printf("argv[0]: %s\n", argv[0]);
    //printf("argv[1]: %s\n", argv[1]);
    //printf("argv[2]: %s\n", argv[2]);

    char *newargv[] = { NULL, argv[2], NULL };
    char *newenv[] = { NULL };

    // This is important
    newargv[0] = argv[1];

    execve(argv[1], newargv, newenv);

    return 0;
}
