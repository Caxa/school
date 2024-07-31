FLAGS = -Wall -Wextra -Werror=format-security
CC = gcc
BUILD_DIR = ../build

.PHONY: all clean rebuild

all: strtok_tests strlen_tests strstr_tests strchr_tests strcat_tests strcpy_tests strcmp_tests

# Test targets
s21_string.o: s21_string.c
	$(CC) -c s21_string.c -o s21_string.o


strtok_tests: s21_string.o s21_string_test.c 
	$(CC) -D Quest_7 s21_string.o s21_string_test.c -o $(BUILD_DIR)/Quest_7

strstr_tests: s21_string.o s21_string_test.c
	$(CC) -D Quest_6 s21_string.o s21_string_test.c -o $(BUILD_DIR)/Quest_6

strchr_tests: s21_string.o s21_string_test.c 
	$(CC) -D Quest_5 s21_string.o s21_string_test.c -o $(BUILD_DIR)/Quest_5

strcat_tests: s21_string.o s21_string_test.c 
	$(CC) -D Quest_4 s21_string.o s21_string_test.c -o $(BUILD_DIR)/Quest_4

strcpy_tests: s21_string.o s21_string_test.c 
	$(CC) -D Quest_3 s21_string.o s21_string_test.c -o $(BUILD_DIR)/Quest_3

strcmp_tests: s21_string.o s21_string_test.c 
	$(CC) -D Quest_2 s21_string.o s21_string_test.c -o $(BUILD_DIR)/Quest_2

strlen_tests: s21_string.o s21_string_test.c 
	$(CC) -D Quest_1 s21_string.o s21_string_test.c -o $(BUILD_DIR)/Quest_1

# Object file rules


clean:
	rm -rf *.o *.a *.so $(BUILD_DIR)/*

rebuild: clean all
