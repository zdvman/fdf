/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:17:10 by dzuiev            #+#    #+#             */
/*   Updated: 2024/02/10 16:03:13 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

int				ft_putchar(char c);
int				ft_putstr(char *s);
int				ft_atoi(const char *nptr);
long			ft_atol(const char *str);
long long		ft_atoll(const char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
void			*ft_memset(void *str, int c, size_t len);
void			ft_bzero(void *str, size_t len);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
size_t			ft_strlen(const char *str);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
size_t			ft_strlcat(char *dest, const char *src, size_t size);
char			*ft_strchr(const char *str, int character);
char			*ft_strrchr(const char *str, int character);
char			*ft_strnstr(const char *haystack, const char *needle,
					size_t len);
int				ft_isalpha(int character);
int				ft_isdigit(int character);
int				ft_isalnum(int character);
int				ft_isascii(int character);
int				ft_isspace(char c);
int				ft_isprint(int character);
int				ft_toupper(int character);
int				ft_tolower(int character);
int				ft_lstsize(t_list *lst);
int				ft_putnchar(char c, int n);
int				ft_putnstr(char *str, int len);
int				ft_issign(int c);
int				ft_isnumber(char *arg);
int				ft_iszero(char *arg);
int				ft_strisempty(char *arg);
int				ft_strisspace_only(char *str);
int				ft_duplicates_found(char **argv);
int				ft_nbr_strcmp(const char *s1, const char *s2);
char			*ft_strdup(const char *str);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			*ft_calloc(size_t nmemb, size_t size);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
void			ft_swap(int *a, int *b);
t_list			*ft_lstnew(void *content);
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void(*del)(void *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
void			*ft_realloc(void *ptr, size_t size);
char			*get_next_line(int fd);

#endif
