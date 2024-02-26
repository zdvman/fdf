/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:37:02 by dzuiev            #+#    #+#             */
/*   Updated: 2024/02/20 19:37:02 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libpipex.h"
#include <stdio.h>
#include <string.h>

static size_t	ft_wordlen(const char *s, char c);
static size_t	ft_count_words(const char *s, char c);
static char		**ft_split_result(char **result, char const *s, char c, int i);

char	**ft_split(char const *s, char c)
{
	char	**result;

	if (s == NULL)
		return (NULL);
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

int main(int argc, char **argv, char **envp)
{

	int		i;
	char	*path;
	char	**dirs;

	i = 0;
	path = NULL;
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = strdup(envp[i]);
			if (!path)
			{
				perror("ft_strdup");
				exit(EXIT_FAILURE);
			}
			break ;
		}
		i++;
	}
	// printf("%s\n", path);



	dirs = ft_split(NULL, ':');
	i = 0;
	while (dirs)
	{
		printf("%s\n", *dirs);
		dirs++;
	}
	while (dirs[i])
	{
		free(dirs[i]);
		i++;
	}
	free(dirs);
	free(path);
	return (0);
}
