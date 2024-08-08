TARGET1 = ../../build/Quest_3
TARGET2 = ../../build/Quest_5
TARGET3 = ../../build/Quest_6
TARGET4 = ../../build/Quest_4
CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf *.o *.a *.so
LIB_DIR = ~/lib 
LIB_NAME = libdata_process.so

all : $(TARGET1)

$(TARGET1) : main.o io.o stat.o process.o decision.o
	$(CC) -o $(TARGET1) main.o io.o stat.o process.o decision.o 

io.o: ../data_libs/data_io.c
	$(CC) $(CFLAGS) -c ../data_libs/data_io.c -o io.o

stat.o: ../data_libs/data_stat.c
	$(CC) $(CFLAGS) -c ../data_libs/data_stat.c -o stat.o

process.o: ../data_module/data_process.c
	$(CC) $(CFLAGS) -c ../data_module/data_process.c -o process.o

decision.o: ../yet_another_decision_module/decision.c
	$(CC) $(CFLAGS) -c ../yet_another_decision_module/decision.c -o decision.o

main.o: main_executable_module.c
	$(CC) $(CFLAGS) -c main_executable_module.c -o main.o

data_stat.a: stat.o
	ar rc libdata_stat.a stat.o
	ranlib libdata_stat.a

build_with_static: main.o io.o data_stat.a process.o decision.o
	$(CC) -o $(TARGET2) main.o io.o process.o decision.o -L. -ldata_stat

data_process.so: ../data_module/data_process.c stat.o
	$(CC) -fPIC -c ../data_module/data_process.c
	$(CC) -shared -o libdata_process.so data_process.o stat.o


build_with_dynamic: main.o io.o stat.o process.o decision.o data_process.so
	@mkdir -p $(LIB_DIR)  # Создание директории lib в домашней директории
	@cp $(LIB_NAME) $(LIB_DIR)  # Копирование библиотеки в домашнюю директорию
	@cp $(LIB_NAME) ~  # Копирование библиотеки в домашнюю директорию
	$(CC) main.o io.o -L. -ldata_process decision.o -Wl,-rpath,$(LIB_DIR) -o $(TARGET3)
io_macro.so: ../data_libs/data_io_macro.h
	$(CC) -c ../data_libs/data_io_macro.h -o io_macro.o

build_with_macro: io_macro.so main.o stat.o process.o decision.o
	$(CC) main.o stat.o process.o decision.o  -o $(TARGET4)

clean:
	$(RM)

rebuild:
	$(MAKE) clean
	$(MAKE) all
