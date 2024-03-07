# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/07 11:21:50 by dzuiev            #+#    #+#              #
#    Updated: 2024/03/07 11:21:50 by dzuiev           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                             Makefile for fdf                           #
#                                                                              #
# **************************************************************************** #

# Имена исполняемых файлов для основной и бонусной частей проекта
NAME = fdf
# BONUS_NAME = fdf

# Компилятор и флаги компиляции
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

# Директории с исходным кодом и библиотеками
LIBMLX_DIR = minilibx-linux
LIBFT_DIR = libft
INCLUDES = includes
SRC_DIR = src
OBJ_DIR = obj
BONUS_DIR = src_bonus
OBJ_BONUS_DIR = obj_bonus

# Поиск исходных файлов и создание объектных файлов
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS_WITHOUT_MAIN = $(filter-out $(OBJ_DIR)/fdf.o, $(OBJS))

BONUS_SRCS = $(wildcard $(BONUS_DIR)/*.c)
BONUS_OBJS = $(BONUS_SRCS:$(BONUS_DIR)/%.c=$(OBJ_BONUS_DIR)/%.o)

# Статические библиотеки для основной и бонусной частей
LIBMLX = $(LIBMLX_DIR)/libmlx_Linux.a
LIBFT = $(LIBFT_DIR)/libft.a
LIBFDF = libfdf.a

# Основная цель - сборка основной части проекта
all: $(NAME)

# Сборка основной части проекта
$(NAME): $(LIBFDF) $(LIBFT) $(LIBMLX) $(OBJ_DIR)/fdf.o
	$(CC) $(CFLAGS) -I$(INCLUDES) -o $(NAME) $(OBJ_DIR)/fdf.o -L. -lfdf -L$(LIBFT_DIR) -lft -L$(LIBMLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz

# Сборка бонусной части проекта если имя программы
# для бонусной части отличное от основной части (не используется)
# $(BONUS_NAME): $(LIBFDF) $(LIBFT) $(BONUS_OBJS)
#	$(CC) $(CFLAGS) -I$(INCLUDES) -o $(BONUS_NAME) $(BONUS_OBJS) -L. -lfdf -L$(LIBFT_DIR) -lft

# Компиляция библиотеки libmlx_Linux
$(LIBMLX):
	$(MAKE) -C $(LIBMLX_DIR)

# Компиляция библиотеки libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Создание статической библиотеки libfdf.a из объектных файлов
$(LIBFDF): $(OBJS_WITHOUT_MAIN)
	ar rcs $(LIBFDF) $(OBJS_WITHOUT_MAIN)

# Компиляция исходных файлов в объектные файлы
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDES) -O3 -c $< -o $@

# Компиляция исходных файлов бонусной части в объектные файлы
$(OBJ_BONUS_DIR)/%.o: $(BONUS_DIR)/%.c
	@mkdir -p $(OBJ_BONUS_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDES) -O3 -c $< -o $@

# Цель для сборки бонусной части проекта
bonus: $(LIBFDF) $(LIBFT) $(LIBMLX) $(BONUS_OBJS)
	$(CC) $(CFLAGS) -I$(INCLUDES) -o $(NAME) $(BONUS_OBJS) -L. -lfdf -L$(LIBFT_DIR) -lft -L$(LIBMLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz

# Очистка всех созданных файлов
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(LIBMLX_DIR) clean
	rm -rf $(OBJ_DIR) $(OBJ_BONUS_DIR) $(LIBFDF)

# Полная очистка проекта
fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME) 
# rm -f file2
# rm -f file
# rm -f $(BONUS_NAME)

# Пересборка проекта
re: fclean all

# Указание фиктивных целей
.PHONY: all clean fclean re bonus
