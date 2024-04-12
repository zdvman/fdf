# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/10 10:31:12 by dzuiev            #+#    #+#              #
#    Updated: 2024/04/12 20:20:31 by dzuiev           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** # 
#                                 Minishell                                    #
#  Project structure:                                                          #
#   minishell/                                                                 #
#  ├── libft/              # Libft library files                               #
#  │   ├── Makefile                                                            #
#  │   └── ...             # Libft source files and headers                    #
#  ├── src/                # Source files for Minishell                        #
#  │   ├── core/           # Core functionality for both parts                 #
#  │   │   └── ...         # Core implementation files                         #
#  │   ├── mandatory/      # Mandatory specific files                          #
#  │   │   └── ...         # Mandatory implementation files                    #
#  │   ├── bonus/          # Bonus specific files (if any)                     #
#  │   │   └── ...         # Bonus implementation files                        #
#  │   └── main.c          # Main program entry point                          #
#  ├── includes/           # Header files                                      #
#  │   ├── minishell.h                                                         #
#  │   └── bonus_features.h                                                    #
#  ├── Makefile                                                                #
#  └── README.md                                                               #
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
# Name of the executable file for the main and bonus parts of the project
NAME = minishell
# **************************************************************************** #

# **************************************************************************** #
# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
# **************************************************************************** #

# **************************************************************************** #
# Name of the libft and libminishell libraries
LIBFT = $(LIBFT_DIR)/libft.a
LIBMINISHELL = libminishell.a
# **************************************************************************** #

# **************************************************************************** #
# Directories with source files and libraries
LIBFT_DIR = libft # path to the libft library
INCLUDES = includes # path to the header files
SRC_CORE_DIR = src/core # path to the core source files
OBJ_CORE_DIR = obj/core # path to the core object files
SRC_MANDATORY_DIR = src/mandatory # path to the mandatory source files
OBJ_MANDATORY_DIR = obj/mandatory # path to the mandatory object files
SRC_BONUS_DIR = src/bonus # path to the bonus source files
OBJ_BONUS_DIR = obj/bonus # path to the bonus object files
# **************************************************************************** #

# **************************************************************************** #
# Source files for the main part of the project
SRC_CORE = $(wildcard $(SRC_CORE_DIR)/*.c)
OBJ_CORE = $(SRC_CORE:$(SRC_CORE_DIR)/%.c=$(OBJ_CORE_DIR)/%.o)
# **************************************************************************** #

# **************************************************************************** #
# Source files for the main part of the project
SRC_MANDATORY = $(wildcard $(SRC_MANDATORY_DIR)/*.c)
OBJ_MANDATORY = $(SRC_MANDATORY:$(SRC_MANDATORY_DIR)/%.c=$(OBJ_MANDATORY_DIR)/%.o)
# **************************************************************************** #

# **************************************************************************** #
# Source files for the bonus part of the project
SRC_BONUS = $(wildcard $(SRC_BONUS_DIR)/*.c)
OBJ_BONUS = $(SRC_BONUS:$(SRC_BONUS_DIR)/%.c=$(OBJ_BONUS_DIR)/%.o)
# **************************************************************************** #

# **************************************************************************** #
# Rule to compile source files into object files
$(OBJ_CORE_DIR)/%.o: $(SRC_CORE_DIR)/%.c
	mkdir -p $(OBJ_CORE_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@
# **************************************************************************** #

# **************************************************************************** #
# Rule to compile source files into object files
$(OBJ_MANDATORY_DIR)/%.o: $(SRC_MANDATORY_DIR)/%.c
	mkdir -p $(OBJ_MANDATORY_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@
# **************************************************************************** #

# **************************************************************************** #
# Rule to compile source files into object files
$(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c
	mkdir -p $(OBJ_BONUS_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@
# **************************************************************************** #

# **************************************************************************** #
# Main target
all: $(NAME)
	@echo "$(GREEN)Compilation successful: $(NAME)$(RESET)"
# **************************************************************************** #

# **************************************************************************** #
# Linking the executable
$(NAME): $(LIBFT) $(LIBMINISHELL) $(OBJ_MANDATORY)
	$(CC) $(CFLAGS) -I$(INCLUDES) $(OBJ_MANDATORY) $(LIBFT) $(LIBMINISHELL) -o $(NAME)
# **************************************************************************** #

# **************************************************************************** #
# Bonus part compilation
bonus: CFLAGS += -DBONUS
bonus: $(LIBFT) $(LIBMINISHELL) $(OBJ_BONUS)
	$(CC) $(CFLAGS) -I$(INCLUDES) $(OBJ_BONUS) $(LIBFT) $(LIBMINISHELL) -o $(NAME)
# **************************************************************************** #

# **************************************************************************** #
# Cleaning up
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_CORE_DIR) $(OBJ_MANDATORY_DIR) $(OBJ_BONUS_DIR)
# **************************************************************************** #

# **************************************************************************** #
# Full cleaning
fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(LIBMINISHELL) $(NAME)
# **************************************************************************** #

# **************************************************************************** #
# Rebuild everything
re: fclean all
# **************************************************************************** #

# **************************************************************************** #
# Phony targets
.PHONY: all clean fclean re bonus
# **************************************************************************** #
