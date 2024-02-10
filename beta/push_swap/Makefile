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

# Program names
NAME           = push_swap
NAME_BONUS     = checker

# Directories
LIBFT_DIR      = libft
SRC_DIR        = src
OBJ_DIR        = obj
INCLUDE_DIR    = include
BONUS_DIR      = src_bonus
OBJ_BONUS_DIR  = obj_bonus

# Source files
SRCS           = $(shell find $(SRC_DIR) -name '*.c' ! -name 'push_swap.c')
OBJS           = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
BONUS_SRCS     = $(shell find $(BONUS_DIR) -name '*.c')
BONUS_OBJS     = $(BONUS_SRCS:$(BONUS_DIR)/%.c=$(OBJ_BONUS_DIR)/%.o)
MAIN_SRC       = $(SRC_DIR)/push_swap.c
BONUS_MAIN_SRC = $(BONUS_DIR)/checker.c

# Compiler and flags
CC             = gcc
CFLAGS         = -Wall -Wextra -Werror

# Libraries
LIBFT          = $(LIBFT_DIR)/libft.a
LIBPS          = libpush_swap.a

# Compile libraries and programs
all: $(LIBFT) $(LIBPS) $(NAME)

$(NAME): $(MAIN_SRC) $(LIBFT) $(LIBPS)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -o $(NAME) $(MAIN_SRC) -L. -lpush_swap -L$(LIBFT_DIR) -lft

bonus: $(LIBFT) $(LIBPS) $(NAME_BONUS)

$(NAME_BONUS): $(BONUS_MAIN_SRC) $(LIBFT) $(LIBPS)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -o $(NAME_BONUS) $(BONUS_MAIN_SRC) -L. -lpush_swap -L$(LIBFT_DIR) -lft

# Compile libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Compile libpush_swap.a
$(LIBPS): $(OBJS)
	ar rcs $(LIBPS) $(OBJS)

# Compiling .c to .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(OBJ_BONUS_DIR)/%.o: $(BONUS_DIR)/%.c
	@mkdir -p $(OBJ_BONUS_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Cleaning rules
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR) $(OBJ_BONUS_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME) $(NAME_BONUS) $(LIBPS)

re: fclean all

.PHONY: all clean fclean re bonus
