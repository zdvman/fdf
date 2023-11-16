/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:03:34 by dzuiev            #+#    #+#             */
/*   Updated: 2023/11/16 00:18:18 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
char	*get_next_line(int fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *str, int character);
size_t	ft_strlen(const char *str);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memset(void *str, int c, size_t len);
int		ft_lstsize(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	dealloc(t_list *list);
char	*ft_strdup(const char *str);
t_list	*create_linked_list(int fd, char *buf, t_list *list);
char	*next_line_from_list(t_list *list);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void *realloc(void *ptr, size_t size);

#endif
