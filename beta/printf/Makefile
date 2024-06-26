# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/10 10:47:10 by dzuiev            #+#    #+#              #
#    Updated: 2023/12/05 15:16:36 by dzuiev           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the library
NAME			= libftprintf.a

# Path to libft directory (relative to the Makefile)
LIBFT_DIR		= ../libft
# Create the list of used functions from libft (found by find_used_libft_funcs.sh)
LIBFT_USED_SRCS	= $(shell sh find_used_libft_funcs.sh)
# Convert .c files to .o files for libft used in printf
LIBFT_OBJS		= $(patsubst $(LIBFT_DIR)/%.c,$(LIBFT_DIR)/obj/%.o,$(LIBFT_USED_SRCS))

# Source files of the library (all .c files in src directory)
SRCS			= $(shell find src -name 'ft_*.c')
# Convert .c files to .o files for the library (in obj directory)
OBJS			= $(patsubst src/%.c,obj/%.o,$(SRCS))

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g
RM				= rm -rf
AR				= ar crs

# Main rule for the library
$(NAME):		objdir $(LIBFT_OBJS) $(OBJS)
				$(AR) $(NAME) $(OBJS) $(LIBFT_OBJS)

# Rule for libft
$(LIBFT):		$(LIBFT_OBJS)
				@mkdir -p $(LIBFT_DIR)/obj
				$(AR) $(LIBFT) $(LIBFT_OBJS)

# Rule for compiling libft .c to .o (in obj directory of libft)
$(LIBFT_DIR)/obj/%.o:	$(LIBFT_DIR)/%.c
				@mkdir -p $(LIBFT_DIR)/obj
				$(CC) $(CFLAGS) -c $< -o $@

# Generic rule for compiling .c to .o (in obj directory)
obj/%.o:		src/%.c
				@mkdir -p obj
				$(CC) $(CFLAGS) -c $< -o $@

# Rule for creating the obj directory (if needed)
objdir:
				@mkdir -p obj
				@mkdir -p $(LIBFT_DIR)/obj

# Rule for all
all:			$(NAME)

bonus:			$(NAME)

# Rule for cleaning object files and the obj directory
clean:
				$(RM) obj
				$(RM) $(LIBFT_DIR)/obj

# Rule for full clean (includes removing the library and the obj directory)
fclean:	 		clean
				$(RM) $(NAME)
				$(RM) $(LIBFT)
				$(RM) test

# Rule for re-making everything
re:				fclean all

# Rule for compiling and running tests (Adjust as needed)
test:			$(NAME)
				$(CC) $(CFLAGS) -o test tests/main.c -L. -lftprintf

# Marking phony targets
.PHONY:			all clean fclean re test objdir bonus
