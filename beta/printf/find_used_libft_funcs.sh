#!/bin/bash

# Путь к исходным файлам ft_printf
PRINTF_SRCS="src/*.c"

# Путь к libft
LIBFT_DIR="../libft"

# Найти все вызовы функций libft в исходных файлах ft_printf
USED_LIBFT_FUNCS=$(grep -oh "ft_[a-zA-Z_]*" $PRINTF_SRCS | sort | uniq)

# Печатаем список файлов .c, соответствующих этим функциям
for func in $USED_LIBFT_FUNCS; do
    src_file="$LIBFT_DIR/${func}.c"
    if [ -f "$src_file" ]; then
        echo "$src_file"
    fi
done
