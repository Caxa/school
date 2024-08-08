#include "modules.h"

#include <stdio.h>

#include "shared.h"

void get_all_active_modules() {
    FILE *file = fopen(MODULES_FILE, "rb");
    if (!file) {
        perror("Cannot open modules file");
        return;
    }

    Module module;
    while (fread(&module, sizeof(Module), 1, file)) {
        if (module.active) {
            printf("ID: %d, Name: %s, Active: %d\n", module.id, module.name, module.active);
        }
    }
    fclose(file);
}

void get_modules_at_first_level() {
    FILE *file = fopen(MEMORY_LEVELS_FILE, "rb");
    if (!file) {
        perror("Cannot open memory levels file");
        return;
    }

    MemoryLevel memory_level;
    while (fread(&memory_level, sizeof(MemoryLevel), 1, file)) {
        if (memory_level.level == 1) {
            FILE *mod_file = fopen(MODULES_FILE, "rb");
            if (!mod_file) {
                perror("Cannot open modules file");
                fclose(file);
                return;
            }

            Module module;
            while (fread(&module, sizeof(Module), 1, mod_file)) {
                if (module.id == memory_level.module_id) {
                    printf("Module ID: %d, Name: %s, Level: %d\n", module.id, module.name,
                           memory_level.level);
                }
            }
            fclose(mod_file);
        }
    }
    fclose(file);
}
