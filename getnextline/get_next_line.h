/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:03:34 by dzuiev            #+#    #+#             */
/*   Updated: 2023/11/13 18:11:54 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE
# endif

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct s_list
{
	char		*str_buf;
	struct s_list	*next;
}			t_list;

char	*get_next_line(int fd);
t_list	*ft_lstlast(t_list *list);
void    dealloc(t_list **list, t_list *clean_list, char *buf);
void    prepare_next_list(t_list **list);
void    copy_str(t_list *list, char *str);
int     len_to_newline(t_list *list);
char    *get_line(t_list *list);
void    append(t_list **list, char *buf);
void    create_list_from_line(t_list **list, fd);

#endif
