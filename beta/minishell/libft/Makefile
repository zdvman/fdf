# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/30 11:17:38 by dzuiev            #+#    #+#              #
#    Updated: 2024/04/12 20:14:16 by dzuiev           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the library
NAME = libft.a

# Colors for messages
GREEN=\033[0;32m
YELLOW=\033[0;33m
RED=\033[0;31m
BLUE=\033[0;34m
RESET=\033[0m

# Source and object directories
SRC_DIR = .
OBJ_DIR = obj

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Sources and objects
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Bonus files
BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
		ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
BONUS_OBJS = $(addprefix $(OBJ_DIR)/, $(BONUS:.c=.o))

# Compile the library
$(NAME): $(OBJS)
	@ar rcs $@ $^
	@echo "$(GREEN)Compilation successful: $(NAME)$(RESET)"

# Compile object files into obj directory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
# @echo "$(BLUE)Compiled $< into $@$(RESET)"
# mkdir -p $(OBJ_DIR) - create a directory $(OBJ_DIR) if it doesn't exist
# -p - no error if existing, make parent directories as needed 

# Main target
all: $(NAME)

# Clean object files
clean:
	@ if [ -d $(OBJ_DIR) ]; then \
		rm -rf $(OBJ_DIR); \
		echo "$(YELLOW)Libft object files removed$(RESET)"; \
	fi
# rm -rf $(OBJ_DIR) - remove the directory $(OBJ_DIR) with all its content
# -r - remove directories and their contents recursively
# -f - ignore nonexistent files and arguments, never prompt

# Full clean including the library
fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) removed$(RESET)"

# Rebuild the library
re: fclean all

# Compile bonus files
bonus: $(OBJS) $(BONUS_OBJS)
	@ar rcs $(NAME) $^
	@echo "$(GREEN)Bonus part compiled: $(NAME)$(RESET)"
# ar rcs $(NAME) $^ - create a static library $(NAME) from object files $^ (all object files)
# $^ - all object files (OBJS and BONUS_OBJS)

# Phony targets
.PHONY: all clean fclean re bonus
