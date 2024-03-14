/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:58:58 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/14 19:23:43 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libfdf.h"

static void	get_map_size(char *file, t_fdf *data, t_img *img)
{
	open_file(data, img, file, 0);
	data->line = get_next_line(data->fd);
	if (data->line != NULL)
		data->width = ft_count_words(data->line, ' ');
	if (data->width == 0)
		cleanup(data, img, "Error: empty file\n", 1);
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
	data->zoom = data->win_width * data->win_height
		/ data->width * data->height;
}

static void	create_map(int y, char *line, t_fdf *data, t_img *img)
{
	char	**split;
	char	**tmp;
	int		x;

	split = ft_split(line, ' ');
	if (split == NULL)
		cleanup(data, img, "Error: split error in create_map function\n", 1);
	x = 0;
	while (split[x] != NULL && x < data->width)
	{
		tmp = ft_split(split[x], ',');
		data->my_map[y][x] = (int *)malloc(2 * sizeof(int));
		if (data->my_map[y][x] == NULL || tmp == NULL)
			cleanup(data, img,
				"Error: malloc error in create_map function\n", 1);
		data->my_map[y][x][0] = ft_atoi(tmp[0]);
		if (tmp[1] != NULL)
			data->my_map[y][x][1] = ft_atoi_base(tmp[1], 16);
		else
			data->my_map[y][x][1] = 0;
		ft_free_array((void ***)&tmp);
		x++;
	}
	data->my_map[y][x] = NULL;
	ft_free_array((void ***)&split);
}

void	read_map(char *file, t_fdf *data, t_img *img)
{
	int	y;

	y = 0;
	get_map_size(file, data, img);
	data->my_map = (int ***)malloc((data->height + 1) * sizeof(int **));
	if (data->my_map == NULL)
		cleanup(data, img, "Error: malloc error in read_map function\n", 1);
	open_file(data, img, file, 0);
	data->line = get_next_line(data->fd);
	while (data->line != NULL)
	{
		data->my_map[y] = (int **)malloc((data->width + 1) * sizeof(int *));
		if (data->my_map[y] == NULL)
			cleanup(data, img, "Error: malloc error in read_map function\n", 1);
		create_map(y, data->line, data, img);
		free(data->line);
		data->line = NULL;
		data->line = get_next_line(data->fd);
		y++;
	}
	data->my_map[y] = NULL;
	ft_free_ptr((void **)&data->line);
	close(data->fd);
	data->fd = -1;
}
