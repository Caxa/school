CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
CLIBS = -lm

BUILD_PATH = ../build
SRC_OUT_TEST = ./data_output_test.c ./data_input_output.c 


all:

out-tests:
	$(CC) $(CFLAGS) $(CLIBS) $(SRC_OUT_TEST) -o $(BUILD_PATH)/run_out_test


format-check:
	cp ../materials/linters/.clang-format .
	clang-format -n *.c *.h

format: format-check
	clang-format -i *.c *.h
	rm ./.clang-format

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem ./*.c ./*.h

clean:
	rm ../build/run_*

# point_struct.h        | Структура точки с двумя координатами (х,у)
# data_input_output.c   | Файл, содержащий функции ввода/вывода
# data_input_output.h   | Хедер, содержащий прототипы ввода/вывода
# data_output_test.c    | Тестер, содержит тест для функции y = sin(x)
