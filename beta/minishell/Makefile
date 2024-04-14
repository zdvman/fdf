# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/10 10:31:12 by dzuiev            #+#    #+#              #
#    Updated: 2024/04/14 21:08:13 by dzuiev           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                 Minishell                                    #
#  Project structure:                                                          #
#   minishell/                                                                 #
#  ├── libft/                  # Libft library files                           #
#  │   ├── obj/                # Libft object files                            #
#  │   ├── Makefile            # Makefile to build the libft library           #
#  │   └── ...                 # Libft source files and headers                #
#  ├── src/                    # Source files for Minishell core functionality #
#  │   ├── mandatory/          # Source files from mandatory sources           #
#  │   ├── bonus/              # Source files from bonus sources               #
#  │   └── main.c              # Main file for the Minishell project           #
#  ├── includes/               # Header files for all Minishell parts          #
#  │   ├── minishell.h         # Main headers for the project                  #
#  │   └── minishell_bonus.h   # Bonus headers for the project                 #
#  ├── obj/                    # Object files for all Minishell parts          #
#  │   ├── mandatory/          # Object files from mandatory sources           #
#  │   ├── bonus/              # Object files from bonus sources               #
#  ├── Makefile                # Makefile to build the minishell project       #
#  └── README.md               # Documentation of the project                  #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# Colors for messages
GREEN=\033[0;32m
YELLOW=\033[0;33m
RED=\033[0;31m
BLUE=\033[0;34m
RESET=\033[0m
# **************************************************************************** #

# **************************************************************************** #
# Basic Configurations
NAME = minishell # Name of the executable file
CC = cc # Compiler
CFLAGS = -Wall -Wextra -Werror -g # Flags
LIBFT = $(LIBFT_DIR)/libft.a # Libft library
# **************************************************************************** #

# **************************************************************************** #
# Directories with source files and libraries
LIBFT_DIR = libft
LIBFT_DIR = libft
INCLUDES = -I./includes -I$(LIBFT_DIR)
LDFLAGS = -L$(LIBFT_DIR) -lft -lreadline #-lreadhistory -L/usr/local/lib , ldconfig -p | grep readline
SRC_DIR = src
OBJ_DIR = obj
SRC_MANDATORY_DIR = $(SRC_DIR)/mandatory
OBJ_MANDATORY_DIR = $(OBJ_DIR)/mandatory
SRC_BONUS_DIR = $(SRC_DIR)/bonus
OBJ_BONUS_DIR = $(OBJ_DIR)/bonus
# **************************************************************************** #

# **************************************************************************** #
# Source and Object files mapping for mandatory and bonus parts
SRC = $(wildcard $(SRC_DIR)/*.c) # All source files in current directory (main.c)
SRC_MANDATORY = $(wildcard $(SRC_MANDATORY_DIR)/*.c)
SRC_BONUS = $(wildcard $(SRC_BONUS_DIR)/*.c)

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o) # All object files in current directory
OBJ_MANDATORY = $(SRC_MANDATORY:$(SRC_MANDATORY_DIR)/%.c=$(OBJ_MANDATORY_DIR)/%.o)
OBJ_BONUS = $(SRC_BONUS:$(SRC_BONUS_DIR)/%.c=$(OBJ_BONUS_DIR)/%.o)
# **************************************************************************** #

# **************************************************************************** #
# Main target
all: $(NAME)

# Linking the executable
$(NAME): $(LIBFT) $(OBJ) $(OBJ_MANDATORY)
	@$(CC) -o $@ $(LIBFT) $(OBJ) $(OBJ_MANDATORY) $(LDFLAGS)
	@echo "$(GREEN)$(NAME) compiled$(RESET)"

# -o $@ - output file name $(NAME), $@ = $(NAME)
# **************************************************************************** #

# Compile libft library
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "$(GREEN)Libft compiled$(RESET)"
# **************************************************************************** #

# **************************************************************************** #
# Rules for compiling source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_MANDATORY_DIR)/%.o: $(SRC_MANDATORY_DIR)/%.c
	@mkdir -p $(OBJ_MANDATORY_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c
	@mkdir -p $(OBJ_BONUS_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# -c $< -o $@ - compile source file $< into object file $@,
# $< = source file, $@ = object file
# **************************************************************************** #

# Bonus part compilation
bonus: CFLAGS += -DBONUS # Add a flag to the compiler
bonus:  $(OBJ_BONUS) $(LIBFT) $(OBJ) $(OBJ_MANDATORY)
	@$(CC) -o $(NAME) $(LIBFT) $(OBJ) $(OBJ_MANDATORY) $(OBJ_BONUS) $(LDFLAGS)
	@echo "$(GREEN)$(NAME) compiled with bonus part$(RESET)"
# **************************************************************************** #
# Cleaning up
clean:
	@ if [ -d $(OBJ_DIR) ]; then \
		rm -rf $(OBJ_DIR); \
		echo "$(YELLOW)Minishell object files removed$(RESET)"; \
	fi
	@$(MAKE) -C $(LIBFT_DIR) clean

# Full cleaning
fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) removed$(RESET)"

# Rebuild everything
re: fclean all

# **************************************************************************** #
# Phony targets
.PHONY: all clean fclean re bonus
# **************************************************************************** #

# В контексте Makefile, команда -c $< -o $@ используется для указания компилятору ($(CC))
# как компилировать исходные файлы в объектные файлы. Вот детальное объяснение каждого компонента этой команды:

# -c
# Этот флаг говорит компилятору генерировать объектный файл (*.o) из исходного файла (*.c).
# Он останавливает процесс после этапа компиляции, не переходя к этапу линковки,
# который обычно следует за компиляцией при создании исполняемого файла.

# $<
# Это одна из автоматических переменных в Makefile, которая представляет имя первой зависимости текущего правила.
# В контексте правил компиляции, где правило выглядит как $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c,
# $< будет подставлено значением исходного файла .c, который нужно скомпилировать.

# -o
# Этот флаг используется для указания выходного файла компиляции. Следом за этим флагом должно идти имя файла,
# в который будет записан результат компиляции (в данном случае, объектный файл).

# $@
# Это также автоматическая переменная в Makefile, которая представляет имя цели текущего правила.
# В контексте правила, например, $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c, $@ будет заменено на имя объектного файла,
# который должен быть сгенерирован. Это позволяет обеспечить, что каждый исходный файл будет компилироваться
# в соответствующий объектный файл в указанной директории.
