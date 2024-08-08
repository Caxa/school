// logger.h
#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <time.h>

#include "log_levels.h"  // Ensure this is included to use log levels

FILE* log_init(const char* filename);  // Use const char* for better practice
int logcat(FILE* log_file, const char* message, enum log_level level);
int log_close(FILE* log_file);

#endif  // LOGGER_H
