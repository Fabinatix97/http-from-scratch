#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("Now running the %s progam\n", argv[0]);
    printf("%s, bye!\n", argv[1]);
    exit(EXIT_SUCCESS);
}
