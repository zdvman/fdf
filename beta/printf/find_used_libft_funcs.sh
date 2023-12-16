#!/bin/bash

# Path to ft_printf sources
PRINTF_SRCS="src/*.c"

# Path- to libft sources
LIBFT_DIR="../libft"

# Find all used libft functions in ft_printf
USED_LIBFT_FUNCS=$(grep -oh "ft_[a-zA-Z_]*" $PRINTF_SRCS | sort | uniq)

# Print all used libft functions with their source file
for func in $USED_LIBFT_FUNCS; do
	src_file="$LIBFT_DIR/${func}.c"
	if [ -f "$src_file" ]; then
		echo "$src_file"
	fi
done
