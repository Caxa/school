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

void print_records(const char *filename);
void sort_records(const char *filename);
void add_record(const char *filename);
int compare_records(const void *a, const void *b);

int main() {
    char filename[256];
    scanf("%255s", filename);  // Ограничиваем длину ввода
    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 0:
            print_records(filename);
            break;
        case 1:
            sort_records(filename);
            break;
        case 2:
            add_record(filename);
            sort_records(filename);
            break;
        default:
            printf("n/a\n");
    }

    return 0;  // Завершаем программу после выполнения пункта меню
}

void print_records(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("n/a\n");
        return;
    }

    Record record;
    int count = 0;

    while (fread(&record, sizeof(Record), 1, file)) {
        printf("%d %d %d %d %d %d %d %d\n", record.year, record.month, record.day, record.hour, record.minute,
               record.second, record.status, record.code);
        count++;
    }

    fclose(file);
    if (count == 0) {
        printf("n/a\n");
    }
}

void sort_records(const char *filename) {
    FILE *file = fopen(filename, "rb+");
    if (!file) {
        printf("n/a\n");
        return;
    }

    size_t capacity = 10;
    Record *records = malloc(capacity * sizeof(Record));
    if (!records) {
        printf("n/a\n");
        fclose(file);
        return;
    }

    size_t count = 0;
    while (fread(&records[count], sizeof(Record), 1, file) == 1) {
        count++;
        if (count >= capacity) {
            capacity *= 2;
            records = realloc(records, capacity * sizeof(Record));
            if (!records) {
                printf("n/a\n");
                fclose(file);
                return;
            }
        }
    }

    if (count == 0) {
        printf("n/a\n");
        free(records);
        fclose(file);
        return;
    }

    qsort(records, count, sizeof(Record), compare_records);

    rewind(file);
    fwrite(records, sizeof(Record), count, file);
    fflush(file);
    fclose(file);
    free(records);

    print_records(filename);
}

void add_record(const char *filename) {
    FILE *file = fopen(filename, "ab");
    if (!file) {
        printf("n/a\n");
        return;
    }

    Record record;
    scanf("%d %d %d %d %d %d %d %d", &record.year, &record.month, &record.day, &record.hour, &record.minute,
          &record.second, &record.status, &record.code);

    fwrite(&record, sizeof(Record), 1, file);
    fclose(file);
}

int compare_records(const void *a, const void *b) {
    const Record *recordA = (const Record *)a;
    const Record *recordB = (const Record *)b;

    if (recordA->year != recordB->year) return recordA->year - recordB->year;
    if (recordA->month != recordB->month) return recordA->month - recordB->month;
    if (recordA->day != recordB->day) return recordA->day - recordB->day;
    if (recordA->hour != recordB->hour) return recordA->hour - recordB->hour;
    if (recordA->minute != recordB->minute) return recordA->minute - recordB->minute;
    return recordA->second - recordB->second;
}
