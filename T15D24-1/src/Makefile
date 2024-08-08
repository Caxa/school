CC = gcc
CFLAGS = -Wall

OBJ = shared.o modules.o memory_levels.o modules_db.o

all: build_db

p: $(OBJ)
	$(CC) $(CFLAGS) -o ../build/modules_db.o $(OBJ)

build_db: $(OBJ) p
	$(CC) $(CFLAGS) -o $@ $(OBJ)

shared.o: shared.c shared.h
	$(CC) $(CFLAGS) -c shared.c

modules.o: modules.c modules.h shared.h
	$(CC) $(CFLAGS) -c modules.c

memory_levels.o: memory_levels.c memory_levels.h shared.h
	$(CC) $(CFLAGS) -c memory_levels.c

modules_db.o: modules_db.c modules.h memory_levels.h shared.h
	$(CC) $(CFLAGS) -c modules_db.c

clean:
	rm -f *.o modules_db
