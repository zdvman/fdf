/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 14:50:51 by dzuiev            #+#    #+#             */
/*   Updated: 2023/12/29 17:53:44 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int	ft_isdigit(int character)
{
	if (character >= '0' && character <= '9')
		return (1);
	return (0);
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

static size_t	ft_wordlen(const char *s, char c);
static size_t	ft_count_words(const char *s, char c);
static char		**ft_split_result(char **result, char const *s, char c, int i);

char	**ft_split(char const *s, char c)
{
	char	**result;

	result = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!result)
		return (NULL);
	return (ft_split_result(result, s, c, 0));
}

static char	**ft_split_result(char **result, char const *s, char c, int i)
{
	int	j;
	int	k;

	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		result[j] = (char *)malloc(sizeof(char) * (ft_wordlen(s + i, c) + 1));
		if (!result[j])
		{
			while (j > 0)
				free(result[--j]);
			free(result);
			return (NULL);
		}
		k = 0;
		while (s[i] && s[i] != c)
			result[j][k++] = s[i++];
		result[j++][k] = '\0';
	}
	result[j] = NULL;
	return (result);
}

static size_t	ft_wordlen(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static size_t	ft_count_words(const char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			i += ft_wordlen(&s[i], c);
		}
		else
			i++;
	}
	return (count);
}

int	ft_error_input(char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (argv[i])
	{
		if (ft_strchr(argv[i], ' ') == NULL)
			while (argv[i][j])
			{
				if(!ft_isdigit(argv[i][j]))
				return (1);
				j++;
			}
		else
		{
			ft

		}

		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int	*num_arr;

	if (argc < 2)
	{
		write(1, "Error\n", 6);	
		return (-1);
	}
	if (argc == 2)
	{
		num_arr = ft_split(argv[1], ' ');
		if (ft_error_input(argv))
		{
			write(1, "Error\n", 6);
			return (-1);
		}
	}
	if (ft_error_input(argv))
	{
		write(1, "Error\n", 6);
		return (-1);
	}
	return (0);
}
