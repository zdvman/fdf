# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/14 18:09:17 by dzuiev            #+#    #+#              #
#    Updated: 2023/11/14 18:09:17 by dzuiev           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	$(wildcard *.c)
OBJS			= $(SRCS:.c=.o)

#BONUS			=	$(wildcard ft_*_bonus.c)
#BONUS_OBJS		= $(BONUS:.c=.o)

CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

NAME			= get_next_line.a

test: $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) -o test

all:			$(NAME)

$(NAME):		$(OBJS)
				ar rcs $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS) 
#				$(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

#bonus:			$(OBJS) $(BONUS_OBJS)
#				ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)

.PHONY:			all clean fclean re 
#bonus
