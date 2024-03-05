/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:24:25 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/04 15:40:56 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libpipex.h"

void	ft_free_array(char ***array)
{
	int	i;

	if (!*array)
		return ;
	i = 0;
	while ((*array)[i])
	{
		free((*array)[i]);
		i++;
	}
	free(*array);
	*array = NULL;
}

char	*get_env(char **envp)
{
	int		i;
	char	*path;

	path = NULL;
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = envp[i] + 5;
			return (path);
		}
	}
	return (NULL);
}

char	*get_full_path(char **dirs, int i, char *cmd)
{
	char	*temp_path;
	char	*full_path;

	temp_path = ft_strjoin(dirs[i], "/");
	if (!temp_path)
	{
		perror("ft_strjoin");
		return (NULL);
	}
	full_path = ft_strjoin(temp_path, cmd);
	free(temp_path);
	if (!full_path)
	{
		perror("ft_strjoin");
		return (NULL);
	}
	return (full_path);
}

char	*get_path(char *cmd, char *path)
{
	char	**dirs;
	char	*full_path;
	int		i;

	i = -1;
	full_path = NULL;
	dirs = ft_split(path, ':');
	if (!dirs)
		return (NULL);
	while (dirs[++i])
	{
		full_path = get_full_path(dirs, i, cmd);
		if (full_path == NULL)
			break ;
		if (access(full_path, X_OK) == 0 && access(full_path, F_OK) == 0)
		{
			ft_free_array(&dirs);
			return (full_path);
		}
		free(full_path);
		full_path = NULL;
	}
	ft_free_array(&dirs);
	return (cmd);
}
