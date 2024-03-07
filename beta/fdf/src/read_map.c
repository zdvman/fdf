/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:58:58 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/07 18:58:58 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libfdf.h"

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

static size_t	get_map_size(char *file, t_fdf *fdf)
{
	open_file(fdf, file, 0);
	fdf->line = get_next_line(fdf->fd);
	if (fdf->line != NULL)
		fdf->width = ft_count_words(fdf->line, ' ');
	while (fdf->line != NULL)
	{
		fdf->height++;
		free(fdf->line);
		fdf->line = NULL;
		fdf->line = get_next_line(fdf->fd);
	}
	free(fdf->line);
	fdf->line = NULL;
	close(fdf->fd);
	fdf->fd = -1;
	return (fdf->height * fdf->width);
}

static int	create_map(int i, int y, char *line, t_fdf *fdf)
{
	char	**split;
	int		x;

	split = ft_split(line, ' ');
	if (split == NULL)
		cleanup(fdf, "Error: split error in create_map function\n", 1);
	x = 0;
	while (split[x] != NULL)
	{
		fdf->my_map[i] = (int *)malloc(3 * sizeof(int));
		if (fdf->my_map[i] == NULL)
			cleanup(fdf, "Error: malloc error in create_map function\n", 1);
		fdf->my_map[i][0] = x;
		fdf->my_map[i][1] = y;
		fdf->my_map[i][2] = ft_atoi(split[x]);
		x++;
		i++;
	}
	ft_free_array((void ***)&split);
	return (i);
}

void	read_map(char *file, t_fdf *fdf)
{
	int	y;
	int	i;

	fdf->my_map = (int **)malloc((get_map_size(file, fdf) + 1) * sizeof(int *));
	if (fdf->my_map == NULL)
		cleanup(fdf, "Error: malloc error in read_map function\n", 1);
	i = 0;
	y = 0;
	open_file(fdf, file, 0);
	fdf->line = get_next_line(fdf->fd);
	while (fdf->line != NULL)
	{
		i = create_map(i, y, fdf->line, fdf);
		free(fdf->line);
		fdf->line = NULL;
		fdf->line = get_next_line(fdf->fd);
		y++;
	}
	fdf->my_map[i] = NULL;
	free(fdf->line);
	fdf->line = NULL;
	close(fdf->fd);
	fdf->fd = -1;
}
