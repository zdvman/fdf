# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/19 09:20:47 by dzuiev            #+#    #+#              #
#    Updated: 2024/03/19 09:20:47 by dzuiev           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                        Makefile for philosophers                             #
#                                                                              #
# **************************************************************************** #

# Имена исполняемых файлов для основной и бонусной частей проекта
NAME = philo
BONUS_NAME = philo_bonus

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
OBJS_WITHOUT_MAIN = $(filter-out $(OBJ_DIR)/philo.o, $(OBJS))

BONUS_SRCS = $(wildcard $(BONUS_DIR)/*.c)
BONUS_OBJS = $(BONUS_SRCS:$(BONUS_DIR)/%.c=$(OBJ_BONUS_DIR)/%.o)

# Статические библиотеки для основной и бонусной частей
LIBFT = $(LIBFT_DIR)/libft.a
LIBPHILO = libphilo.a

# Основная цель - сборка основной части проекта
all: $(NAME)

# Цель для сборки бонусной части проекта
bonus: $(BONUS_NAME)

#  Сборка основной части проекта
$(NAME): $(LIBPHILO) $(LIBFT) $(OBJ_DIR)/philo.o
	$(CC) $(CFLAGS) -I$(INCLUDES) -o $(NAME) $(OBJ_DIR)/philo.o -L. -lphilo -L$(LIBFT_DIR) -lft -lpthread

# Сборка бонусной части проекта если имя программы
# для бонусной части отличное от основной части
$(BONUS_NAME): $(LIBPHILO) $(LIBFT) $(BONUS_OBJS)
	$(CC) $(CFLAGS) -I$(INCLUDES) -o $(BONUS_NAME) $(BONUS_OBJS) -L. -lphilo -L$(LIBFT_DIR) -lft -lpthread

# Компиляция библиотеки libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Создание статической библиотеки libphilo.a из объектных файлов
$(LIBPHILO): $(OBJS_WITHOUT_MAIN)
	ar rcs $(LIBPHILO) $(OBJS_WITHOUT_MAIN)

# Компиляция исходных файлов в объектные файлы
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDES) -O3 -c $< -o $@

# Компиляция исходных файлов бонусной части в объектные файлы
$(OBJ_BONUS_DIR)/%.o: $(BONUS_DIR)/%.c
	@mkdir -p $(OBJ_BONUS_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDES) -O3 -c $< -o $@

# when you have the same name for the bonus and mandaatory program
# bonus: $(LIBPHILO) $(LIBFT) $(BONUS_OBJS)
# 	$(CC) $(CFLAGS) -I$(INCLUDES) -o $(NAME) $(BONUS_OBJS) -L. -lphilo -L$(LIBFT_DIR) -lft -lpthread

# Очистка всех созданных файлов
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR) $(OBJ_BONUS_DIR) $(LIBPHILO)

# Полная очистка проекта
fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	rm -f $(BONUS_NAME)

# Пересборка проекта
re: fclean all

# Указание фиктивных целей
.PHONY: all clean fclean re bonus
