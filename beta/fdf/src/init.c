/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:00:16 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/07 19:00:16 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libfdf.h"

void	init_default(t_fdf *data, t_img *img)
{
	data->img = img;
	data->key_states = ft_calloc(65536 , sizeof(int));
	data->fd = -1;
	data->width = 0;
	data->height = 0;
	data->zoom = 20;
	data->color = 0xFFFFFF;
	data->z_color = 0xFF0000;
	data->shift_x = 0;
	data->shift_y = 0;
	data->angle_x = 0.615;
	data->angle_y = 0.785;
	data->angle_z = 0.0;
	data->last_x = 0;
	data->last_y = 0;
	data->line = NULL;
	data->my_map = NULL;
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	img->img_ptr = NULL;
	img->img_pixel_ptr = NULL;
	img->bits_per_pixel = 0;
	img->endian = 0;
	img->line_length = 0;
}

int	close_window(void *param)
{
	t_fdf	*data;

	data = (t_fdf *)param;
	mlx_loop_end(data->mlx_ptr);
	return (0);
}

void	open_window(t_fdf *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		cleanup(data, NULL, "Error: mlx_init() failed\n", 1);
	mlx_get_screen_size(data->mlx_ptr,
		&data->win_width,
		&data->win_height);
	data->win_ptr = mlx_new_window(data->mlx_ptr,
			data->win_width,
			data->win_height, "FDF");
	if (data->win_ptr == NULL)
		cleanup(data, NULL, "Error: mlx_new_window() failed\n", 1);
	data->shift_x = data->win_width / 2 - data->width * data->zoom / 2;
	data->shift_y = data->win_height / 2 - data->height * data->zoom / 2;
	data->img->img_width = data->win_width;
	data->img->img_height = data->win_height;
	data->img->img_ptr = mlx_new_image(data->mlx_ptr,
			data->img->img_width,
			data->img->img_height);
	if (data->img->img_ptr == NULL)
		cleanup(data, data->img, "Error: mlx_new_image() failed\n", 1);
	data->img->img_pixel_ptr = mlx_get_data_addr(data->img->img_ptr,
			&data->img->bits_per_pixel,
			&data->img->line_length,
			&data->img->endian);
}
