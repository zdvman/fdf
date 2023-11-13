/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:07:39 by dzuiev            #+#    #+#             */
/*   Updated: 2023/11/13 18:09:53 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


t_list	*ft_lstlast(t_list *list)
{
	if (list)
	{
		while (list->next)
		{
			list = list->next;
		}
	}
	return (list);
}

void	dealloc(t_list **list, t_list *clean_list, char *buf)
{
	t_list	*tmp;

	if (*list == NULL)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->str_buf);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (clean_list->str_buf[0])
		*list = clean_node;
	else
	{
		free(buf);
		free(clean_node);
	}
}


void	prepare_next_list(t_list **list)
{
	t_list	*last_node;
	t_list	*clean_node;
	int	i;
	int	j;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	if (buf == NULL || clean_node ==NULL)
		return ;
	last_node = ft_lstlast(list);

	i = 0;
	j = 0;
	while (last_node->str_buf[i] != '\0'
		&& last_node->str_buf[j] != '\n')
		i++;
	while (last_node->str_buf[i] != '\0'
		&& last_node->str_buf[++i])
		buff[j++] = last_node->str_buf[i];
	buf[j] = '\0';
	clean_node->str_buf = buf;
	clean_node->next = NULL;
	dealloc(list, clean_node, buf);
}

void	copy_str(t_list *list, char *str)
{
	int	i;
	int	j;
	if (list == NULL)
		return ;
	while (list)
	{
		i = 0;
		while (list->str_buf[i])
		{
			if (list->buf[i] = '\n')
			{
				str[j++] = '\n';
				str[j] = '\0';
				return ;
			}
			str[j++] = list->str_buf[i++];
		}
		list = list->next;
	}
	str[j] = '\0';
}

int	len_to_newline(t_list *list)
{
	int	i;
	int	len;

	if (list == NULL)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->strbuf[i])
		{
			len++;
			return (len);
		}
		i++;
		len++;
	}
	list = list->next;
	return (len);
}

char	*get_line(t_list *list)
{
	int	str_len;
	char	*next_str;

	if (list == NULL)
		return (NULL);
	str_len = len_to_newline(list);
	next_str = malloc(str_len + 1);
	if (next_str == NULL)
		return (NULL);
	copy_str(list, next_str)
	return (next_str);
}

void	append(t_list **list, char *buf)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = ft_lstlast(list);
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	if (last_node == NULL)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->str_buf = buf;
	new_node->next = NULL;
}

void	create_list_from_line(t_list **list, fd)
{
	int	char_read;
	char	*buf;

	while(!found_new_line(*list))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (buf == NULL)
			return ;

		char_read = read(fd, buf, BUFFER_SIZE);
		if (!char_read)
		{
			free(buf);
			return ;
		}
		buf[char_read] = '\0';
		// Append the Node
		append(list, buf);
	}
}

