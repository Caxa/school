#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 10000

typedef struct {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int status;
    int code;
} DoorState;

int is_within_range(DoorState record, int start_day, int start_month, int start_year, int end_day,
                    int end_month, int end_year) {
    int record_date = record.year * 10000 + record.month * 100 + record.day;
    int start_date = start_year * 10000 + start_month * 100 + start_day;
    int end_date = end_year * 10000 + end_month * 100 + end_day;

    return (record_date >= start_date && record_date <= end_date);
}

void clear_records(const char *filename, int start_day, int start_month, int start_year, int end_day,
                   int end_month, int end_year) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("n/a\n");
        return;
    }

    DoorState *records = malloc(MAX_RECORDS * sizeof(DoorState));
    if (!records) {
        printf("n/a\n");
        fclose(file);
        return;
    }

    int count = 0;

    while (fread(&records[count], sizeof(DoorState), 1, file) == 1) {
        count++;
        if (count >= MAX_RECORDS) {
            printf("n/a\n");
            break;
        }
    }
    fclose(file);

    if (count == 0) {
        printf("n/a\n");
        free(records);
        return;
    }

    FILE *new_file = fopen("temp_file.bin", "wb");
    if (!new_file) {
        printf("n/a\n");
        free(records);
        return;
    }

    for (int i = 0; i < count; i++) {
        if (!is_within_range(records[i], start_day, start_month, start_year, end_day, end_month, end_year)) {
            fwrite(&records[i], sizeof(DoorState), 1, new_file);
        }
    }
    fclose(new_file);

    free(records);

    file = fopen("temp_file.bin", "rb");
    if (!file) {
        printf("n/a\n");
        return;
    }

    records = malloc(MAX_RECORDS * sizeof(DoorState));
    if (!records) {
        printf("n/a\n");
        fclose(file);
        return;
    }

    count = 0;
    while (fread(&records[count], sizeof(DoorState), 1, file) == 1) {
        // Change the printf format to match the required output
        printf("%d %d %d %d %d %d %d %d\n", records[count].year, records[count].month, records[count].day,
               records[count].hour, records[count].minute, records[count].second, records[count].status,
               records[count].code);
        count++;
    }
    fclose(file);
    free(records);
}

int main() {
    char filename[256];

    if (scanf("%255s", filename) != 1) {
        printf("n/a\n");
        return 1;
    }

    int start_day, start_month, start_year;
    int end_day, end_month, end_year;

    if (scanf("%d.%d.%d %d.%d.%d", &start_day, &start_month, &start_year, &end_day, &end_month, &end_year) !=
        6) {
        printf("n/a\n");
        return 1;
    }

    if (start_year > end_year || (start_year == end_year && start_month > end_month) ||
        (start_year == end_year && start_month == end_month && start_day > end_day)) {
        printf("n/a\n");
        return 1;
    }

    clear_records(filename, start_day, start_month, start_year, end_day, end_month, end_year);

    return 0;
}
