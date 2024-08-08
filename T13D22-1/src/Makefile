CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11
BUILD = ../build
TARGET = cipher

# List of object files
OBJ = cipher.o logger.o  # Add logger.o here

all: cipher

# Rule to compile cipher.c
cipher.o: cipher.c
	$(CC) $(FLAGS) -c cipher.c

# Rule to compile logger.c
logger.o: logger.c logger.h
	$(CC) $(FLAGS) -c logger.c

# Rule to link the object files into the final executable
cipher: $(OBJ)
	$(CC) $(OBJ) -o $(BUILD)/$(TARGET)

clean:
	rm -rf *.o *.a *.so $(BUILD)/*

copy: t.txt cipher.c logger.h
	cp t.txt cipher.c logger.h $(BUILD)

rebuild: clean all copy

.PHONY: all clean rebuild copy cipher
