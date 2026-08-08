#include <stdio.h>

int main() {
    // create new file
    FILE *fptr;
    fptr = fopen("mynewfile", "w");
    fclose(fptr);

    // insert some text
    fopen("mynewfile", "w");
    if(fptr == NULL) {
        printf("The file does not exist");
        return 1;
    }
    fprintf(fptr, "Hello there");
    fclose(fptr);

    // append some text
    fopen("mynewfile", "a");
    if(fptr == NULL) {
        printf("The file does not exist");
        return 1;
    }
    fprintf(fptr, "\nBye-bye");
    fclose(fptr);
    
    // read from a file
    fptr = fopen("mynewfile", "r");
    if(fptr == NULL) {
        printf("The file does not exist");
        return 1;
    }
    char myString[100];
    while(fgets(myString, 100, fptr)) {
        printf("%s", myString);
    }
    fclose(fptr);

    return 0;
}
