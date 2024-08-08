#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int status;  // 0 или 1
    int code;
} Record;

int search_record(const char *filename, const char *date_str);

int main() {
    char filename[256];
    char date_str[11];  // Формат "ДД.ММ.ГГГГ"

    printf("Введите путь к файлу: ");
    scanf("%255s", filename);  // Ограничиваем длину ввода

    printf("Введите дату в формате ДД.ММ.ГГГГ: ");
    scanf("%10s", date_str);  // Ограничиваем длину ввода

    int code = search_record(filename, date_str);
    if (code == -1) {
        printf("n/a\n");
    } else {
        printf("%d\n", code);
    }

    return 0;
}

int search_record(const char *filename, const char *date_str) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        return -1;  // Ошибка открытия файла
    }

    Record record;
    char search_day[3], search_month[3], search_year[5];
    sscanf(date_str, "%2s.%2s.%4s", search_day, search_month, search_year);

    int day = atoi(search_day);
    int month = atoi(search_month);
    int year = atoi(search_year);

    while (fread(&record, sizeof(Record), 1, file)) {
        if (record.day == day && record.month == month && record.year == year) {
            fclose(file);
            return record.code;  // Возвращаем код первой найденной записи
        }
    }

    fclose(file);
    return -1;  // Запись не найдена
}
