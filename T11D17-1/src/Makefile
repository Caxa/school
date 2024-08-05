FLAGS = -Wall -Wextra -Werror -std=c11
CC = gcc 
BUILD_DIR = ../build
TARGET1 = Quest_1
TARGET2 = Quest_2
TARGET3 = Quest_3

.PHONY: all clean rebuild door_struct list_test

all: door_struct list_test stack_test

dmanager_module.o : dmanager_module.c
	$(CC) $(FLAGS) -c dmanager_module.c -o dmanager_module.o 

door_struct : dmanager_module.o
	$(CC) -o $(BUILD_DIR)/$(TARGET1)  dmanager_module.c

list.o : list.c
	$(CC) $(FLAGS) -c list.c -o list.o

list_test :  list.o list_test.c
	$(CC) $(FLAGS) list.o list_test.c -o $(BUILD_DIR)/$(TARGET2)

stack.o : stack.c 
	$(CC) $(FLAGS) -c stack.c -o stack.o

stack_test :  stack.o stack_test.c
	$(CC) $(FLAGS) stack.o stack_test.c -o $(BUILD_DIR)/$(TARGET3)

clean:
	rm -rf *.o *.a *.so $(BUILD_DIR)/*

rebuild: clean all

