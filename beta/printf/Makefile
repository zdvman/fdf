# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/10 10:47:10 by dzuiev            #+#    #+#              #
#    Updated: 2023/11/10 13:49:33 by dzuiev           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= libftprintf.a

SRCS			=	$(wildcard ft_*.c)
OBJS			= $(SRCS:.c=.o)

#BONUS			=	$(wildcard ft_*_bonus.c)
#BONUS_OBJS		= $(BONUS:.c=.o)

CC				= cc
CFLAGS			= -Wall -Wextra -Werror
RM				= rm -rf
AR				= ar crs


test:			
				$(CC) $(CFLAGS) $(SRCS) main.c

$(NAME):		$(OBJS)
				$(AR) $(NAME) $(OBJS)

all:			$(NAME)

clean:
				$(RM) $(OBJS) 
#				$(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

#bonus:			$(OBJS) $(BONUS_OBJS)
#				ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)

.PHONY:			all clean fclean re test
#bonus
