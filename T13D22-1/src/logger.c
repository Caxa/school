#include "logger.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "log_levels.h"

FILE *log_init(const char *filename) {  // Change char* to const char*
    FILE *log_file = fopen(filename, "a");
    if (log_file == NULL) {
        printf("Could not open log file\n");
    }
    return log_file;
}

int logcat(FILE *log_file, const char *message, enum log_level level) {  // Change char* to const char*
    if (log_file == NULL) return 1;

    time_t now = time(NULL);
    char *time_str = ctime(&now);
    time_str[strlen(time_str) - 1] = '\0';  // Remove newline character

    char *level_str;
    switch (level) {
        case DEBUG:
            level_str = "DEBUG";
            break;
        case TRACE:
            level_str = "TRACE";
            break;
        case INFO:
            level_str = "INFO";
            break;
        case WARNING:
            level_str = "WARNING";
            break;
        case ERROR:
            level_str = "ERROR";
            break;
        default:
            level_str = "UNKNOWN";
            break;
    }

    fprintf(log_file, "[%s] %s: %s\n", time_str, level_str, message);
    return 0;
}
int log_close(FILE *log_file) {
    if (log_file == NULL) return 1;
    fclose(log_file);
    return 0;
}

// The rest of your logger.c code remains unchanged
