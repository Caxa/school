#ifndef SHARED_H
#define SHARED_H

// Пример структуры для таблицы modules
typedef struct {
    int id;
    char name[100];
    int active;
} Module;

// Пример структуры для таблицы memory_levels
typedef struct {
    int id;
    int module_id;
    int level;
} MemoryLevel;

#define MODULES_FILE "materials/modules.dat"
#define MEMORY_LEVELS_FILE "materials/memory_levels.dat"

// Прототипы функций
void select_modules();
void insert_module(Module module);
void update_module(int id, Module module);
void delete_module(int id);

void select_memory_levels();
void insert_memory_level(MemoryLevel memory_level);
void update_memory_level(int id, MemoryLevel memory_level);
void delete_memory_level(int id);

#endif  // SHARED_H
