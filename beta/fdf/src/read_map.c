/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:58:58 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/11 11:07:41 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libfdf.h"

static int	ft_wordlen(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	ft_count_words(const char *s, char c)
{
	int	i;
	int	count;

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

static void	get_map_size(char *file, t_fdf *data, t_img *img)
{
	open_file(data, img, file, 0);
	data->line = get_next_line(data->fd);
	if (data->line != NULL)
		data->width = ft_count_words(data->line, ' ');
	while (data->line != NULL)
	{
		data->height++;
		free(data->line);
		data->line = NULL;
		data->line = get_next_line(data->fd);
	}
	free(data->line);
	data->line = NULL;
	close(data->fd);
	data->fd = -1;
}

static void	create_map(int y, char *line, t_fdf *data, t_img *img)
{
	char	**split;
	int		x;

	split = ft_split(line, ' ');
	if (split == NULL)
		cleanup(data, img, "Error: split error in create_map function\n", 1);
	x = 0;
	while (split[x] != NULL)
	{
		data->my_map[y][x] = ft_atoi(split[x]);
		x++;
	}
	ft_free_array((void ***)&split);
}

void	read_map(char *file, t_fdf *data, t_img *img)
{
	int	y;

	y = 0;
	get_map_size(file, data, img);
	data->my_map = (int **)malloc((data->height + 1) * sizeof(int *));
	if (data->my_map == NULL)
		cleanup(data, img, "Error: malloc error in read_map function\n", 1);
	open_file(data, img, file, 0);
	data->line = get_next_line(data->fd);
	while (data->line != NULL)
	{
		data->my_map[y] = (int *)malloc((data->width) * sizeof(int));
		if (data->my_map[y] == NULL)
			cleanup(data, img, "Error: malloc error in read_map function\n", 1);
		create_map(y, data->line, data, img);
		free(data->line);
		data->line = NULL;
		data->line = get_next_line(data->fd);
		y++;
	}
	data->my_map[y] = NULL;
	free(data->line);
	data->line = NULL;
	close(data->fd);
	data->fd = -1;
}
