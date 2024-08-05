#include <stdio.h>
#include <stdlib.h>

void print_file_content(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        printf("n/a\n");
        return;
    }
    char ch;
    int flag = 1; 

    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
        flag = 0;
    }

    fclose(file);

    if (flag) {
        printf("n/a\n");
    }
}

int main() {
    int input;
    char file_path[256];

    while (1) {

        if (scanf("%s", file_path) != 1) {
            printf("n/a\n");
            continue;
        }

        if (strcmp(file_path, "-1") == 0) {
            break; 
        }

        print_file_content(file_path);
        printf("\n");
    }

    return 0;
}
