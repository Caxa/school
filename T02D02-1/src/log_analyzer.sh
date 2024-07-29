#!/bin/bash

# Проверяем, передан ли аргумент с путем к файлу
if [ -z "$1" ]; then
    echo "Usage: $0 <path_to_log_file>"
    exit 1
fi

log_file="$1"

# Проверяем существование файла
if [ ! -f "$log_file" ]; then
    echo "File not found: $log_file"
    exit 1
fi

# Общее количество записей
total_records=$(($(wc -l < "$log_file") + 1))

# Количество уникальных файлов
unique_files=$(awk '{print $1}' "$log_file" | sort | uniq | wc -l)

# Количество изменений, вызвавших изменения в хэш-файле
hash_changes=$(awk '{print $1 $8}' "$log_file" | sort | uniq | wc -l)



echo  "$total_records $unique_files $hash_changes"

