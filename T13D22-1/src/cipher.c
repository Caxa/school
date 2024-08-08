#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log_levels.h"
#include "logger.h"

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void print_file_contents(const char *filename, FILE *log_file) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        logcat(log_file, "Could not open file for reading", ERROR);
        printf("n/a");
    } else {
        logcat(log_file, "Opened file for reading", INFO);
        char c;
        int is_empty = 1;
        while ((c = fgetc(file)) != EOF) {
            putchar(c);
            is_empty = 0;
        }
        fclose(file);
        if (is_empty) {
            printf("n/a");
        }
    }
}

void append_to_file(const char *filename, const char *text, FILE *log_file) {
    FILE *file = fopen(filename, "a");
    if (file != NULL) {
        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        if (size > 0) {
            fputs("\n", file);
        }
        fprintf(file, "%s", text);
        logcat(log_file, "Appended text to file", INFO);
        fclose(file);
    } else {
        logcat(log_file, "Could not open file for appending", ERROR);
    }
}

void caesar_cipher(char *str, int shift, FILE *log_file) {
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = 'A' + (str[i] - 'A' + shift + 26) % 26;
        } else if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = 'a' + (str[i] - 'a' + shift + 26) % 26;
        }
    }
    logcat(log_file, "Applied Caesar cipher", INFO);
}

void process_CFiles_in_directory(const char *dirPath, int shift, FILE *log_file) {
    DIR *dir = opendir(dirPath);
    struct dirent *entry;
    if (dir == NULL) {
        logcat(log_file, "Cannot open directory", ERROR);
        printf("n/a\n");
    } else {
        logcat(log_file, "Opened directory for processing .c files", INFO);
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_REG && strstr(entry->d_name, ".c") != NULL) {
                char filePath[512];  // Увеличен размер буфера
                int result = snprintf(filePath, sizeof(filePath), "%s/%s", dirPath, entry->d_name);
                if (result < 0 || (size_t)result >= sizeof(filePath)) {
                    logcat(log_file, "File path too long", ERROR);
                    continue;  // Пропускаем длинные пути
                }
                FILE *file = fopen(filePath, "r");
                if (file != NULL) {
                    char line[1000];
                    FILE *tempFile = fopen("tempfile", "w");
                    while (fgets(line, sizeof(line), file)) {
                        caesar_cipher(line, shift, log_file);
                        fprintf(tempFile, "%s", line);
                    }
                    fclose(file);
                    fclose(tempFile);
                    remove(filePath);
                    rename("tempfile", filePath);
                    logcat(log_file, "Processed and ciphered file", INFO);
                }
            } else if (entry->d_type == DT_REG && strstr(entry->d_name, ".h") != NULL) {
                char filePath[512];  // Увеличен размер буфера
                int result = snprintf(filePath, sizeof(filePath), "%s/%s", dirPath, entry->d_name);
                if (result < 0 || (size_t)result >= sizeof(filePath)) {
                    logcat(log_file, "File path too long", ERROR);
                    continue;  // Пропускаем длинные пути
                }
                FILE *file = fopen(filePath, "w");
                if (file != NULL) {
                    fclose(file);
                    logcat(log_file, "Created header file", INFO);
                }
            }
        }
        closedir(dir);
    }
}
int isCorH(const char *str, char c) {
    int len = strlen(str);
    return (len > 1 && str[len - 1] == c && str[len - 2] == '.');
}

int CaesarCipher(const char *dir, int shift, FILE *log_file) {
    DIR *pDir;
    char name[200];  // Increase buffer size
    snprintf(name, sizeof(name), "../%s", dir);

    pDir = opendir(name);
    if (pDir == NULL) {
        logcat(log_file, "Cannot open directory for Caesar cipher", ERROR);
        printf("n/a\n");
        return 0;
    }
    logcat(log_file, "Opened directory for Caesar cipher", INFO);

    struct dirent *pDirent;
    while ((pDirent = readdir(pDir)) != NULL) {
        char fileName[512];  // Increase buffer size
        size_t result = snprintf(fileName, sizeof(fileName), "%s/%s", name, pDirent->d_name);
        if (result >= sizeof(fileName)) {
            logcat(log_file, "File name too long, skipping", WARNING);
            printf("File name too long: %s/%s\n", name, pDirent->d_name);
            continue;  // Skip file if name is too long
        }

        if (isCorH(pDirent->d_name, 'c')) {
            FILE *fp = fopen(fileName, "r+t");
            if (fp == NULL) {
                logcat(log_file, "Could not open file for reading and ciphering", ERROR);
                printf("n/a\n");
                continue;
            }
            logcat(log_file, "Opened file for ciphering", INFO);

            char buf[500];
            while (fgets(buf, sizeof(buf), fp) != NULL) {
                for (int i = 0; buf[i] != '\0'; i++) {
                    if (buf[i] >= 'A' && buf[i] <= 'Z')
                        buf[i] = 'A' + (buf[i] - 'A' + shift) % 26;
                    else if (buf[i] >= 'a' && buf[i] <= 'z')
                        buf[i] = 'a' + (buf[i] - 'a' + shift) % 26;
                }
                fseek(fp, -strlen(buf), SEEK_CUR);
                fprintf(fp, "%s", buf);
                fflush(fp);
            }
            logcat(log_file, "Completed ciphering for file", INFO);
            fclose(fp);
        }

        if (isCorH(pDirent->d_name, 'h')) {
            FILE *fp = fopen(fileName, "w");
            fclose(fp);
            logcat(log_file, "Created header file", INFO);
        }
    }

    closedir(pDir);
    return 1;
}

int main() {
    int choice = 0;
    char filename[100];
    char inputText[1000];
    int shift;

    FILE *log_file = log_init("cipher.log");
    if (log_file == NULL) {
        return 1;  // If unable to open log file, exit the program
    }

    while (choice != -1) {
        int is_great_number = 1;
        if (scanf("%d", &choice) != 1) {
            clear_input_buffer();
            printf("n/a\n");
            is_great_number = 0;
            continue;
        }
        switch (choice) {
            case 1:
                scanf("%s", filename);
                print_file_contents(filename, log_file);
                printf("\n");
                break;
            case 2:
                clear_input_buffer();
                fgets(inputText, sizeof(inputText), stdin);
                inputText[strcspn(inputText, "\n")] = '\0';
                FILE *checkFile = fopen(filename, "r");
                if (checkFile == NULL) {
                    printf("n/a\n");
                } else {
                    fclose(checkFile);
                    append_to_file(filename, inputText, log_file);
                    print_file_contents(filename, log_file);
                    printf("\n");
                }
                break;
            case 3:
                printf("Enter directory for Caesar cipher: ");
                getchar();  // Clear the buffer
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = 0;  // Remove newline character
                printf("Enter shift value: ");
                scanf("%d", &shift);  // Get shift value for Caesar cipher
                int flag = CaesarCipher(filename, shift, log_file);
                if (flag == 1) {
                    printf("Ciphered files in directory: %s\n", filename);
                } else {
                    printf("Cannot open directory\n");
                }
                break;
            case -1:
                logcat(log_file, "Exiting program", INFO);
                break;
            default:
                if (is_great_number) {
                    clear_input_buffer();
                    printf("n/a\n");
                }
                break;
        }
    }

    log_close(log_file);  // Close the log file before exiting
    return 0;
}
