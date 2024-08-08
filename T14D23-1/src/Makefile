CFLAGS = -Wall -Wextra -Werror -std=c11

all: state_sort state_search clear_state

state_sort: state_sort.c 
	gcc $(CFLAGS) -o ../build/Quest_1 state_sort.c 

state_search: state_search.c
	gcc $(CFLAGS) -o ../build/Quest_2 state_search.c 

clear_state: clear_state.c
	gcc $(CFLAGS) -o ../build/Quest_3 clear_state.c 

clean:
	rm -rf *.o

rebuild: clean all
