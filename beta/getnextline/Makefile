# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/14 18:09:17 by dzuiev            #+#    #+#              #
#    Updated: 2023/11/21 14:06:06 by dzuiev           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	$(filter-out %_bonus.c, $(wildcard *.c))
OBJS			= $(SRCS:.c=.o)

BONUS			=	$(wildcard *_bonus.c)
BONUS_OBJS		= $(BONUS:.c=.o)

CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -g

NAME			= get_next_line.a

test: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -D BUFFER_SIZE=10

btest: $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) -D BUFFER_SIZE=10

all:			$(NAME)

$(NAME):		$(OBJS)
				ar rcs $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME) test btest

re:				fclean $(NAME)

bonus:			$(BONUS_OBJS)
				ar rcs $(NAME) $(BONUS_OBJS)

.PHONY:			all clean fclean re bonus test bteset
