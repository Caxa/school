#ifndef DOOR_STRUCT_H
#define DOOR_STRUCT_H

struct door {
    int id;
    int status;
};

void initialize_doors(struct door* doors);
void sort_doors(struct door* doors, int count);
void print_doors(struct door* doors, int count);

#endif
