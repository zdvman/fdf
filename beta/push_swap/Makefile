# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/10 10:47:10 by dzuiev            #+#    #+#              #
#    Updated: 2024/02/10 17:19:24 by dzuiev           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                             Makefile for push_swap                           #
#                                                                              #
# **************************************************************************** #

# Имена исполняемых файлов для основной и бонусной частей проекта
NAME = push_swap
BONUS_NAME = checker

# Компилятор и флаги компиляции
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

# Директории с исходным кодом и библиотеками
LIBFT_DIR = libft
INCLUDES = includes
SRC_DIR = src
OBJ_DIR = obj
BONUS_DIR = src_bonus
OBJ_BONUS_DIR = obj_bonus

# Поиск исходных файлов и создание объектных файлов
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS_WITHOUT_MAIN = $(filter-out $(OBJ_DIR)/push_swap.o, $(OBJS))

BONUS_SRCS = $(wildcard $(BONUS_DIR)/*.c)
BONUS_OBJS = $(BONUS_SRCS:$(BONUS_DIR)/%.c=$(OBJ_BONUS_DIR)/%.o)

# Статические библиотеки для основной и бонусной частей
LIBFT = $(LIBFT_DIR)/libft.a
LIBPS = libpush_swap.a

# Основная цель - сборка основной части проекта
all: $(NAME)

# Сборка основной части проекта
$(NAME): $(LIBPS) $(LIBFT) $(OBJ_DIR)/push_swap.o
	$(CC) $(CFLAGS) -I$(INCLUDES) -o $(NAME) $(OBJ_DIR)/push_swap.o -L. -lpush_swap -L$(LIBFT_DIR) -lft

# Сборка бонусной части проекта
$(BONUS_NAME): $(LIBPS) $(LIBFT) $(BONUS_OBJS)
	$(CC) $(CFLAGS) -I$(INCLUDES) -o $(BONUS_NAME) $(BONUS_OBJS) -L. -lpush_swap -L$(LIBFT_DIR) -lft

# Компиляция библиотеки libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Создание статической библиотеки libpush_swap.a из объектных файлов
$(LIBPS): $(OBJS_WITHOUT_MAIN)
	ar rcs $(LIBPS) $(OBJS_WITHOUT_MAIN)

# Компиляция исходных файлов в объектные файлы
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

# Компиляция исходных файлов бонусной части в объектные файлы
$(OBJ_BONUS_DIR)/%.o: $(BONUS_DIR)/%.c
	@mkdir -p $(OBJ_BONUS_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

# Цель для сборки бонусной части проекта
bonus: $(BONUS_NAME)

# Очистка всех созданных файлов
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR) $(OBJ_BONUS_DIR) $(LIBPS)

# Полная очистка проекта
fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME) $(BONUS_NAME)
	rm -f commands.txt

# Пересборка проекта
re: fclean all

# Указание фиктивных целей
.PHONY: all clean fclean re bonus
