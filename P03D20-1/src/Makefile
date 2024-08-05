CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
CLIBS = -lm

BUILD_PATH = ../build
SRC_OUT_TEST = ./data_output_test.c ./data_input_output.c 


all: build

out-tests:
	$(CC) $(CFLAGS) $(CLIBS) $(SRC_OUT_TEST) -o $(BUILD_PATH)/run_out_test

build: calculate.o data_input_output.o graph.o polish_notation.o stack.o validation.o
	$(CC) $(CFLAGS) calculate.o data_input_output.o graph.o polish_notation.o stack.o validation.o -o $(BUILD_PATH)/graph

calculate.o: calculate.c
	$(CC) $(CFLAGS) -c calculate.c

calculate_test.o: calculate_test.c
	$(CC) $(CFLAGS) -c calculate_test.c

data_input_output.o: data_input_output.c
	$(CC) $(CFLAGS) -c data_input_output.c

data_output_test.o: data_output_test.c

graph.o: graph.c
	$(CC) $(CFLAGS) -c graph.c

polish_notation.o: polish_notation.c
	$(CC) $(CFLAGS) -c polish_notation.c

polish_notation_test.o: polish_notation_test.c
	$(CC) $(CFLAGS) -c polish_notation_test.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

validation.o: validation.c
	$(CC) $(CFLAGS) -c validation.c

format-check:
	cp ../materials/linters/.clang-format .
	clang-format -n *.c *.h

format: format-check
	clang-format -i *.c *.h
	rm ./.clang-format

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem .

clean:
	rm *.o

# point_struct.h        | Структура точки с двумя координатами (х,у)
# data_input_output.c   | Файл, содержащий функции ввода/вывода
# data_input_output.h   | Хедер, содержащий прототипы ввода/вывода
# data_output_test.c    | Тестер, содержит тест для функции y = sin(x)
