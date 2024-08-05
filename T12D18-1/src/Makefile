CC = gcc
FLAGS = -Wextra -Werror -Wall -std=c11
BUILD = ../build
TARGET = Quest_1
TARGET2 = Quest_2
TARGET3 = Quest_3
TARGET4 = Quest_4
TARGET5 = Quest_5

.PHONY: all clean rebuild print_module.o print_module main_module_entry_point.o bst_create_test bst_insert_test bst_traverse_test documentation_module.o documentation_module

all : print_module bst_create_test bst_insert_test bst_traverse_test documentation_module

print_module.o : print_module.c
	$(CC) -c print_module.c -o print_module.o

print_module : print_module.o main_module_entry_point.c
	$(CC) $(FLAGS) print_module.o main_module_entry_point.c -o $(BUILD)/$(TARGET)

bst.o : bst.c
	$(CC) -c bst.c -o bst.o

bst_create_test : bst_create_test.c bst.o
	$(CC) bst.o bst_create_test.c -o $(BUILD)/$(TARGET3)

bst_insert_test : bst_insert_test.c bst.o
	$(CC) bst.o bst_insert_test.c -o $(BUILD)/$(TARGET4)

bst_traverse_test : bst.o bst_traverse_test.c
	$(CC) bst.o bst_traverse_test.c -o $(BUILD)/$(TARGET5)

documentation_module: documentation_module.c 
	$(CC) $(FLAGS) -D DOC  documentation_module.c main_module_entry_point.c print_module.c -o $(BUILD)/$(TARGET2)

clean :
	rm -rf *.so *.o *.a $(BUILD)/*

rebuild : clean all
