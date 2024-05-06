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

// Функция для инициализации структуры img
static void	init_img_default(t_img *img)
{
	img->img_ptr = NULL;
	img->img_pixel_ptr = NULL;
	img->img_width = 0;
	img->img_height = 0;
	img->bits_per_pixel = 0;
	img->endian = 0;
	img->line_length = 0;
}

// Функция для инициализации структуры line
static void	init_line_default(t_line *line)
{
	line->x = 0;
	line->y = 0;
	line->x1 = 0;
	line->y1 = 0;
	line->color = 0xFFFFFF;
	line->dx = 0;
	line->dy = 0;
	line->sx = 0;
	line->sy = 0;
	line->err = 0;
	line->e2 = 0;
	line->length = 0;
	line->t = 0;
}

// Функция для инициализации структуры data
static void	init_bzezen_data(t_fdf *data)
{
	data->x = 0;
	data->y = 0;
	data->z = 0;
	data->x1 = 0;
	data->y1 = 0;
	data->z1 = 0;
	data->center_x = 0;
	data->center_y = 0;
	data->center_z = 0;
	data->width = 0;
	data->height = 0;
	data->zoom = 1;
	data->color = 0x92FE9D;
	data->z_color = 0;
	data->z1_color = 0;
	data->shift_x = 0;
	data->shift_y = 0;
	data->angle_x = 35.264 * (3.14159265359 / 180);
	data->angle_y = 45 * (3.14159265359 / 180);
	data->angle_z = 0;
	data->angle_step = 0.017;
}

// Функция для инициализации структур по умолчанию
void	init_default(t_fdf *data, t_img *img, t_line *line)
{
	data->grad_flag = 1;
	data->res_step = 1;
	data->shift_index = 1;
	data->z_zoom_index = 4;
	data->img = img;
	data->line_struct = line;
	data->key_states = ft_calloc(65536, sizeof(int));
	data->fd = -1;
	data->last_x = 0;
	data->last_y = 0;
	data->line = NULL;
	data->my_map = NULL;
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	init_bzezen_data(data);
	init_img_default(data->img);
	init_line_default(data->line_struct);
}

// Функция для определения центра карты
void	get_zoom_and_center(t_fdf *data)
{
	float	scale_x;
	float	scale_y;

	scale_x = (data->win_width - 600) / data->width;
	scale_y = (data->win_height - 480) / data->height;
	if (scale_x < scale_y)
		data->zoom = ft_round(scale_x);
	else
		data->zoom = ft_round(scale_y);
	data->shift_x = (data->win_width - data->width * data->zoom) / 2;
	data->shift_y = (data->win_height - data->height * data->zoom) / 2;
	calculate_center(data);
}
