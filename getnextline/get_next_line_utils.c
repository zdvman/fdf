/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:07:39 by dzuiev            #+#    #+#             */
/*   Updated: 2023/11/14 20:56:11 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)ft_calloc((ft_strlen(s1) + ft_strlen(s2)) + 1, 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	return (str);
}

size_t	ft_strlen(const char *str)
{
	size_t	size;

	size = 0;
	while (*(str + size) != '\0')
		size++;
	return (size);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = NULL;
	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	copylen;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (dstlen >= dstsize)
		return (dstsize + srclen);
	if (dstsize - dstlen - 1 > srclen)
		copylen = srclen;
	else
		copylen = dstsize - dstlen - 1;
	ft_memcpy(dst + dstlen, src, copylen);
	dst[dstlen + copylen] = '\0';
	return (dstlen + srclen);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	n;

	n = 0;
	while (size > 1 && *src != '\0')
	{
		*dest++ = *src++;
		n++;
		size--;
	}
	if (size > 0)
		*dest = '\0';
	return (n + ft_strlen(src));
}

t_list	*ft_lstlast(t_list *lst)
{
	if (lst)
	{
		while (lst->next)
		{
			lst = lst->next;
		}
	}
	return (lst);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*ptr_src;
	unsigned char		*ptr_dest;

	if (!dest && !src)
		return (NULL);
	ptr_dest = (unsigned char *)dest;
	ptr_src = (const unsigned char *)src;
	while (n--)
		*ptr_dest++ = *ptr_src++;
	return (dest);
}

char	*ft_strchr(const char *str, int character)
{
	while (*str != (char)character)
	{
		if (!*str)
			return (NULL);
		str++;
	}
	return ((char *)str);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	bytes;
	size_t	overflow;
	void	*ptr;

	if (!nmemb || !size)
		return (malloc(0));
	else
	{
		bytes = nmemb * size;
		overflow = bytes / size;
		if (nmemb != overflow)
			return (NULL);
	}
	ptr = (void *)malloc(bytes);
	if (!ptr)
		return (NULL);
	return (ft_memset(ptr, 0, bytes));
}

void	*ft_memset(void *str, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)str;
	while (len--)
		*ptr++ = (unsigned char)c;
	return (str);
}

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst && new)
	{
		if (*lst)
		{
			last = ft_lstlast(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}

char	*ft_strdup(const char *str)
{
	char	*dup;
	int		i;

	dup = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
