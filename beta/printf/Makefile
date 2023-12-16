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

# Название целевой библиотеки
NAME			= libftprintf.a

# Путь к директории libft
LIBFT_DIR		= ../libft
# Используем скрипт для получения списка исходных файлов из libft, используемых в printf
LIBFT_USED_SRCS	= $(shell sh find_used_libft_funcs.sh)
# Преобразуем исходные файлы .c в объектные файлы .o
LIBFT_OBJS		= $(patsubst $(LIBFT_DIR)/%.c,$(LIBFT_DIR)/obj/%.o,$(LIBFT_USED_SRCS))

# Исходные файлы для ft_printf
SRCS			= $(shell find src -name 'ft_*.c')
# Преобразование исходных файлов в объектные файлы
OBJS			= $(patsubst src/%.c,obj/%.o,$(SRCS))

CC				= cc
CFLAGS			= -Wall -Wextra -Werror
RM				= rm -rf
AR				= ar crs

# Main rule for the library
$(NAME):		objdir $(LIBFT_OBJS) $(OBJS)
				$(AR) $(NAME) $(OBJS) $(LIBFT_OBJS)

# Rule for libft
$(LIBFT):		$(LIBFT_OBJS)
				@mkdir -p $(LIBFT_DIR)/obj
				$(AR) $(LIBFT) $(LIBFT_OBJS)

# Rule for compiling libft .c to .o
$(LIBFT_DIR)/obj/%.o:	$(LIBFT_DIR)/%.c
				@mkdir -p $(LIBFT_DIR)/obj
				$(CC) $(CFLAGS) -c $< -o $@

# Generic rule for compiling .c to .o
obj/%.o:		src/%.c
				@mkdir -p obj
				$(CC) $(CFLAGS) -c $< -o $@

# Объявление правила 'objdir'
objdir:
				@mkdir -p obj
				@mkdir -p $(LIBFT_DIR)/obj

# Rule for all
all:			$(NAME)

# Rule for cleaning object files and the obj directory
clean:
				$(RM) obj
				$(RM) $(LIBFT_DIR)/obj

# Rule for full clean (includes removing the library and the obj directory)
fclean:	 		clean
				$(RM) $(NAME)
				$(RM) $(LIBFT)
				$(RM) test_program

# Rule for re-making everything
re:				fclean all

# Rule for compiling and running tests (Adjust as needed)
test:			$(NAME)
				$(CC) $(CFLAGS) -g -o test_program tests/main.c -L. -lftprintf

# Marking phony targets
.PHONY:			all clean fclean re test objdir
