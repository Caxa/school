#include <stdio.h>
#include <stdlib.h>

#include "memory_levels.h"
#include "modules.h"
#include "shared.h"

void print_main_menu() {
    printf("1. Просмотреть все модули\n");
    printf("2. Добавить модуль\n");
    printf("3. Обновить модуль\n");
    printf("4. Удалить модуль\n");
    printf("5. Просмотреть все уровни памяти\n");
    printf("6. Добавить уровень памяти\n");
    printf("7. Обновить уровень памяти\n");
    printf("8. Удалить уровень памяти\n");
    printf("9. Показать все активные модули\n");
    printf("10. Показать все модули на первом уровне памяти\n");
    printf("11. Показать все уровни памяти для модуля\n");
    printf("0. Выход\n");
}

int main() {
    int choice;
    Module module;
    MemoryLevel memory_level;
    int id;

    while (1) {
        print_main_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                select_modules();
                break;
            case 2:
                printf("Введите ID, Name, Active: ");
                scanf("%d %49s %d", &module.id, module.name, &module.active);
                insert_module(module);
                break;
            case 3:
                printf("Введите ID для обновления: ");
                scanf("%d", &id);
                printf("Введите новые Name и Active: ");
                scanf("%49s %d", module.name, &module.active);
                module.id = id;
                update_module(id, module);
                break;
            case 4:
                printf("Введите ID для удаления: ");
                scanf("%d", &id);
                delete_module(id);
                break;
            case 5:
                select_memory_levels();
                break;
            case 6:
                printf("Введите ID, Module ID, Level: ");
                scanf("%d %d %d", &memory_level.id, &memory_level.module_id, &memory_level.level);
                insert_memory_level(memory_level);
                break;
            case 7:
                printf("Введите ID для обновления: ");
                scanf("%d", &id);
                printf("Введите новые Module ID и Level: ");
                scanf("%d %d", &memory_level.module_id, &memory_level.level);
                memory_level.id = id;
                update_memory_level(id, memory_level);
                break;
            case 8:
                printf("Введите ID для удаления: ");
                scanf("%d", &id);
                delete_memory_level(id);
                break;
            case 9:
                get_all_active_modules();
                break;
            case 10:
                get_modules_at_first_level();
                break;
            case 11:
                printf("Введите Module ID: ");
                scanf("%d", &id);
                get_memory_levels_for_module(id);
                break;
            case 0:
                return 0;
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
    }
    return 0;
}
