#include "memory_levels.h"

#include <stdio.h>

#include "shared.h"

void get_memory_levels_for_module(int module_id) {
    FILE *file = fopen(MEMORY_LEVELS_FILE, "rb");
    if (!file) {
        perror("Cannot open memory levels file");
        return;
    }

    MemoryLevel memory_level;
    while (fread(&memory_level, sizeof(MemoryLevel), 1, file)) {
        if (memory_level.module_id == module_id) {
            printf("ID: %d, Module ID: %d, Level: %d\n", memory_level.id, memory_level.module_id,
                   memory_level.level);
        }
    }
    fclose(file);
}

/*void get_all_memory_levels() {
    FILE *file = fopen(MEMORY_LEVELS_FILE, "rb");
    if (!file) {
        perror("Cannot open memory levels file");
        return;
    }

    MemoryLevel memory_level;
    while (fread(&memory_level, sizeof(MemoryLevel), 1, file)) {
        printf("ID: %d, Module ID: %d, Level: %d\n", memory_level.id, memory_level.module_id,
               memory_level.level);
    }
    fclose(file);
}
*/