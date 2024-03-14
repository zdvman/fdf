/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:32:17 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/14 13:36:17 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libfdf.h"

// Функция для отрисовки пикселя на изображении
static void	put_pixel_to_img(char *buffer, t_fdf *data, t_line *line)
{
	int	pixel_position;

	if (line->x >= 0 && line->x < data->img->img_width
		&& line->y >= 0 && line->y < data->img->img_height)
	{
		pixel_position = line->y * data->img->line_length
			+ line->x * (data->img->bits_per_pixel / 8);
		*(unsigned int *)(buffer + pixel_position)
			= mlx_get_color_value(data->mlx_ptr, line->color);
	}
}

// Функция для инициализации структуры t_line
static void	init_line(t_line *line, t_fdf *data)
{
	line->t = 0;
	line->length = 0;
	line->x = data->x;
	line->y = data->y;
	line->x1 = data->x1;
	line->y1 = data->y1;
	line->dx = ft_abs(line->x1 - line->x);
	line->dy = -ft_abs(line->y1 - line->y);
	if (line->x < line->x1)
		line->sx = 1;
	else
		line->sx = -1;
	if (line->y < line->y1)
		line->sy = 1;
	else
		line->sy = -1;
	line->err = line->dx + line->dy;
	line->length = sqrt(line->dx * line->dx + line->dy * line->dy);
}

// Функция для отрисовки линии
static void	draw_line_loop_body(t_fdf *data, t_line *line)
{
	line->t = sqrt((line->x1 - line->x) * (line->x1 - line->x)
			+ (line->y1 - line->y) * (line->y1 - line->y))
		/ line->length;
	line->color = get_gradient_color(data->z_color,
			data->z1_color, line->t);
	put_pixel_to_img(data->img->img_pixel_ptr, data, line);
	line->e2 = 2 * line->err;
	if (line->e2 >= line->dy)
	{
		line->err += line->dy;
		line->x += line->sx;
	}
	if (line->e2 <= line->dx)
	{
		line->err += line->dx;
		line->y += line->sy;
	}
}

// Функция для отрисовки линии
static void	draw_line(t_fdf *data, t_line *line)
{
	if (data->x >= 0 && data->x < data->img->img_width
		&& data->y >= 0 && data->y < data->img->img_height)
	{
		init_line(line, data);
		while (1)
		{
			if (line->x == line->x1 && line->y == line->y1)
				break ;
			draw_line_loop_body(data, line);
		}
	}
}

// Функция для отрисовки линий
void	ft_brezenham(t_fdf *data)
{
	data->z = data->my_map[data->y][data->x][0];
	data->z1 = data->my_map[data->y1][data->x1][0];
	data->z_color = data->my_map[data->y][data->x][1];
	data->z1_color = data->my_map[data->y1][data->x1][1];
	if (data->z && data->z_color == 0)
		data->z_color = 0xFF0000;
	else if (data->z == 0 && data->z_color == 0)
		data->z_color = data->color;
	if (data->z1 && data->z1_color == 0)
		data->z1_color = 0xFF0000;
	else if (data->z1 == 0 && data->z1_color == 0)
		data->z1_color = data->color;
	data->x *= data->zoom;
	data->y *= data->zoom;
	data->z *= data->zoom / 3;
	data->x1 *= data->zoom;
	data->y1 *= data->zoom;
	data->z1 *= data->zoom / 3;
	rotate_and_project(&data->x, &data->y, &data->z, data);
	rotate_and_project(&data->x1, &data->y1, &data->z1, data);
	data->x += data->shift_x;
	data->y += data->shift_y;
	data->x1 += data->shift_x;
	data->y1 += data->shift_y;
	draw_line(data, data->line_struct);
}
