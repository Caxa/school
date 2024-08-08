#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_file(const char *path) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("n/a");
        return;
    }

    char ch;
    int is_empty = 1; 

    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
        is_empty = 0;
    }

    fclose(file);

    if (is_empty) {
        printf("n/a");
    }
}

void append(const char *path) {
    FILE *file_check = fopen(path, "r");
    if (file_check == NULL) {
        printf("n/a"); 
        return;
    }
    fclose(file_check); 

    FILE *file = fopen(path, "a");
    if (file == NULL) {
        printf("n/a");
        return;
    }
    char input[256];
    getchar();
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    if (strcmp(input, "-1") == 0) {
        fclose(file);
        printf("я тут ");
        return; // Не записываем в файл, просто выходим

    }
        
    
    
    fputs(input, file);
    fclose(file);

    read_file(path);
}

#include <stdio.h>
#include <stdlib.h>

void caesar_cipher(const char *path, int shift) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("n/a");
        return;
    }

    char *buffer = NULL;
    size_t size = 0;
    ssize_t read;

    // Создаем временный файл для записи зашифрованного текста
    FILE *temp_file = fopen("temp.txt", "w");
    if (temp_file == NULL) {
        printf("n/a");
        fclose(file);
        return;
    }

    // Читаем файл построчно
    while ((read = getline(&buffer, &size, file)) != -1) {
        for (ssize_t i = 0; i < read; i++) {
            if (buffer[i] >= 'a' && buffer[i] <= 'z') {
                buffer[i] = (buffer[i] - 'a' + shift) % 26;
                if (buffer[i] < 0) {
                    buffer[i] += 26; // Обработка отрицательных сдвигов
                }
                buffer[i] += 'a'; // Преобразуем обратно в символ
            } else if (buffer[i] >= 'A' && buffer[i] <= 'Z') {
                buffer[i] = (buffer[i] - 'A' + shift) % 26;
                if (buffer[i] < 0) {
                    buffer[i] += 26; // Обработка отрицательных сдвигов
                }
                buffer[i] += 'A'; // Преобразуем обратно в символ
            }
            // Символы новой строки остаются без изменений
        }
        fputs(buffer, temp_file); // Записываем зашифрованную строку во временный файл
    }

    fclose(file);
    fclose(temp_file);
    free(buffer);

    // Заменяем оригинальный файл временным
    remove(path);
    rename("temp.txt", path);
}
/*void clear_header_files(const char *directory) {
    struct dirent *entry;
    DIR *dp = opendir(directory);
    if (dp == NULL) {
        printf("n/a");
        return;
    }

    while ((entry = readdir(dp))) {
        if (entry->d_type == DT_REG) {
            if (strstr(entry->d_name, ".h") != NULL) {
                char filepath[256];
                snprintf(filepath, sizeof(filepath), "%s/%s", directory, entry->d_name);
                remove(filepath);
            }
        }
    }
    closedir(dp);
}
*/


int main() {
    int choice;
    char path[256];
    char last_file[256];
    char dir[256];
    int count=0;
    scanf("%d", &choice);
    scanf("%s", path);

    while (1) {
        if (choice == -1) {
            break;
        } else if (choice == 1) {
            if (count==0){
                read_file(path);
                snprintf(last_file, sizeof(last_file), "%s", path);
                count++;
            }else{
                scanf("%s", path);
                read_file(path);
                snprintf(last_file, sizeof(last_file), "%s", path);
            }
        } else if (choice == 2) {
            append(last_file);
            count++;
        } else if (choice == 3) {
            int shift;
            printf("Введите сдвиг для шифрации: ");
            if(scanf("%d", &shift)==1){
                printf("вводете папку") ;
                scanf("%s",dir);
                caesar_cipher(dir, shift);
            
            }
        } else {
            printf("n/a");
            break;
        }
        scanf("%d", &choice);

    }

    return 0;
}

