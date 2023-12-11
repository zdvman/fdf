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


NAME		= libftprintf.a

LIBFT_DIR	= ../libft
LIBFT		= $(LIBFT_DIR)/libft.a
LIBFT_SRCS	= $(wildcard $(LIBFT_DIR)/*.c)
LIBFT_OBJS  = $(patsubst $(LIBFT_DIR)/%.c,$(LIBFT_DIR)/obj/%.o,$(LIBFT_SRCS))

SRCS		= $(wildcard src/*.c)
OBJS		= $(patsubst src/%.c,obj/%.o,$(SRCS))

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -rf
AR			= ar crs

# Main rule for the library
$(NAME):	$(LIBFT) $(OBJS)
			$(AR) $(NAME) $(OBJS) $(LIBFT_OBJS)

# Rule for libft
$(LIBFT):	$(LIBFT_OBJS)
			$(AR) $(LIBFT) $(LIBFT_OBJS)

# Rule for compiling libft .c to .o
$(LIBFT_DIR)/obj/%.o:	$(LIBFT_DIR)/%.c
			@mkdir -p $(LIBFT_DIR)/obj
			$(CC) $(CFLAGS) -c $< -o $@

# Generic rule for compiling .c to .o
obj/%.o:	src/%.c
			@mkdir -p obj
			$(CC) $(CFLAGS) -c $< -o $@

# Rule for all
all:		$(NAME)

# Rule for cleaning object files and the obj directory
clean:
			$(RM) obj
			$(RM) $(LIBFT_DIR)/obj

# Rule for full clean (includes removing the library and the obj directory)
fclean:	 clean
			$(RM) $(NAME)
			$(RM) $(LIBFT)

# Rule for re-making everything
re:		 fclean all

# Rule for compiling and running tests (Adjust as needed)
test:
			$(CC) $(CFLAGS) -g $(wildcard src/*.c) $(wildcard tests/*.c) -o test_program -L$(LIBFT_DIR) -lft


# Marking phony targets
.PHONY:	 all clean fclean re test
