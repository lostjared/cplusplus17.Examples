#include<stdio.h>
#include<stdlib.h>

int main(int argc, char **argv) {
    if(argc != 2) {
        fprintf(stderr, "Error incorrect arguments..\n");
        return EXIT_FAILURE;
    }
    FILE *fptr = fopen(argv[1], "r");
    if(!fptr) {
        fprintf(stderr, "Error could not open %s\n", argv[1]);
        return EXIT_FAILURE;
    }
    unsigned int index = 1;
    printf("%d: ", index);
    while(!feof(fptr)) {
        char c = fgetc(fptr);
        if(c != EOF) {
            if(c == '\n') {
                index ++;
                printf("\n%d: ", index);
            } else {
                printf("%c", c);
            }
        }
    }
    printf("\n");
    fclose(fptr);
    return EXIT_SUCCESS;
}
