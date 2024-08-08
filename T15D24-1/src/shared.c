#include "shared.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void select_modules() {
    FILE *file = fopen(MODULES_FILE, "rb");
    if (!file) {
        perror("Cannot open modules file");
        return;
    }

    Module module;
    while (fread(&module, sizeof(Module), 1, file)) {
        printf("ID: %d, Name: %s, Active: %d\n", module.id, module.name, module.active);
    }
    fclose(file);
}

void insert_module(Module module) {
    FILE *file = fopen(MODULES_FILE, "ab");
    if (!file) {
        perror("Cannot open modules file");
        return;
    }

    fwrite(&module, sizeof(Module), 1, file);
    fclose(file);
}

void update_module(int id, Module module) {
    FILE *file = fopen(MODULES_FILE, "r+b");
    if (!file) {
        perror("Cannot open modules file");
        return;
    }

    Module current;
    while (fread(&current, sizeof(Module), 1, file)) {
        if (current.id == id) {
            fseek(file, -sizeof(Module), SEEK_CUR);
            fwrite(&module, sizeof(Module), 1, file);
            break;
        }
    }
    fclose(file);
}

void delete_module(int id) {
    FILE *file = fopen(MODULES_FILE, "rb");
    if (!file) {
        perror("Cannot open modules file");
        return;
    }

    FILE *temp = fopen("materials/temp.dat", "wb");
    if (!temp) {
        perror("Cannot open temp file");
        fclose(file);
        return;
    }

    Module module;
    while (fread(&module, sizeof(Module), 1, file)) {
        if (module.id != id) {
            fwrite(&module, sizeof(Module), 1, temp);
        }
    }

    fclose(file);
    fclose(temp);

    remove(MODULES_FILE);
    rename("materials/temp.dat", MODULES_FILE);
}

void select_memory_levels() {
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

void insert_memory_level(MemoryLevel memory_level) {
    FILE *file = fopen(MEMORY_LEVELS_FILE, "ab");
    if (!file) {
        perror("Cannot open memory levels file");
        return;
    }

    fwrite(&memory_level, sizeof(MemoryLevel), 1, file);
    fclose(file);
}

void update_memory_level(int id, MemoryLevel memory_level) {
    FILE *file = fopen(MEMORY_LEVELS_FILE, "r+b");
    if (!file) {
        perror("Cannot open memory levels file");
        return;
    }

    MemoryLevel current;
    while (fread(&current, sizeof(MemoryLevel), 1, file)) {
        if (current.id == id) {
            fseek(file, -sizeof(MemoryLevel), SEEK_CUR);
            fwrite(&memory_level, sizeof(MemoryLevel), 1, file);
            break;
        }
    }
    fclose(file);
}

void delete_memory_level(int id) {
    FILE *file = fopen(MEMORY_LEVELS_FILE, "rb");
    if (!file) {
        perror("Cannot open memory levels file");
        return;
    }

    FILE *temp = fopen("materials/temp.dat", "wb");
    if (!temp) {
        perror("Cannot open temp file");
        fclose(file);
        return;
    }

    MemoryLevel memory_level;
    while (fread(&memory_level, sizeof(MemoryLevel), 1, file)) {
        if (memory_level.id != id) {
            fwrite(&memory_level, sizeof(MemoryLevel), 1, temp);
        }
    }

    fclose(file);
    fclose(temp);

    remove(MEMORY_LEVELS_FILE);
    rename("materials/temp.dat", MEMORY_LEVELS_FILE);
}
