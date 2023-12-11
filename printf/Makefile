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

SRCS		= $(wildcard ft_*.c)
OBJS		= $(SRCS:.c=.o)

# BONUS		= $(wildcard ft_*_bonus.c)
# BONUS_OBJS	= $(BONUS:.c=.o)

CC		= cc
CFLAGS		= -Wall -Wextra -Werror
RM		= rm -rf
AR		= ar crs

# Main rule for the library
$(NAME):	$(OBJS)
		$(AR) $(NAME) $(OBJS)

# Generic rule for compiling .c to .o
%.o:		%.c
		$(CC) $(CFLAGS) -c $< -o $@

# Rule for all
all:		$(NAME)

# Rule for cleaning object files
clean:
		$(RM) $(OBJS) 
#		$(RM) $(BONUS_OBJS)

# Rule for full clean (includes removing the library)
fclean:		clean
		$(RM) $(NAME)

# Rule for re-making everything
re:		fclean all

# bonus:	$(OBJS) $(BONUS_OBJS)
#		$(AR) $(NAME) $(OBJS) $(BONUS_OBJS)

# Rule for compiling and running tests (Adjust as needed)
test:                   
		$(CC) $(CFLAGS) -g $(SRCS) main.c -o test_program

# Marking phony targets
.PHONY: all clean fclean re test
# .PHONY: bonus
