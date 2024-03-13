/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:09:34 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/13 18:44:46 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libfdf.h"

void put_pixel_to_img(char *buffer, t_fdf *data, t_line *line)
{
	int	pixel_position;

	if (line->x >= 0 && line->x < data->img->img_width && line->y >= 0 && line->y < data->img->img_height) 
	{
		pixel_position = line->y * data->img->line_length + line->x * (data->img->bits_per_pixel / 8);
		*(unsigned int *)(buffer + pixel_position) = mlx_get_color_value(data->mlx_ptr, line->color);
	}
}

void rotate_and_project(int *x, int *y, int *z, t_fdf *data)
{
	float xx;
	float yy;
	float zz;
	float tmp_x;
	float tmp_y;
	float tmp_z;

	xx = (float)*x;
	yy = (float)*y;
	zz = (float)*z;
	tmp_x = xx;
	tmp_y = yy;
	tmp_z = zz;
	yy = tmp_y * cos(data->angle_x) - tmp_z * sin(data->angle_x);
	zz = tmp_y * sin(data->angle_x) + tmp_z * cos(data->angle_x);
	tmp_z = zz;
	xx = tmp_x * cos(data->angle_y) + tmp_z * sin(data->angle_y);
	zz = -tmp_x * sin(data->angle_y) + tmp_z * cos(data->angle_y);
	tmp_x = xx;
	tmp_y = yy;
	xx = tmp_x * cos(data->angle_z) - tmp_y * sin(data->angle_z);
	yy = tmp_x * sin(data->angle_z) + tmp_y * cos(data->angle_z);
	*x = ft_round((xx - zz) * sqrt(3) / 2);
	*y = ft_round((xx + 2 * yy + zz) / 2);
}

void	init_line(t_line *line, t_fdf *data)
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
	line->length = sqrt(line->dx*line->dx + line->dy*line->dy);
}

static void draw_line(t_fdf *data, t_line *line)
{
	init_line(line, data);
	while (1)
	{
		line->t = sqrt((line->x1 - line->x)*(line->x1 - line->x) + (line->y1 - line->y)*(line->y1 - line->y)) / line->length;
		line->color = get_gradient_color(data->z_color, data->z1_color, line->t);
		put_pixel_to_img(data->img->img_pixel_ptr, data, line);
		if (line->x == line->x1 && line->y == line->y1)
			break;
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
}

static void	ft_brezenham(t_fdf *data)
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
	data->z *= data->zoom;
	data->x1 *= data->zoom;
	data->y1 *= data->zoom;
	data->z1 *= data->zoom;
	rotate_and_project(&data->x, &data->y, &data->z, data);
	rotate_and_project(&data->x1, &data->y1, &data->z1, data);
	data->x += data->shift_x;
	data->y += data->shift_y;
	data->x1 += data->shift_x;
	data->y1 += data->shift_y;
	draw_line(data, data->line_struct);
}

void	draw_loop_body(int x, int y, t_fdf *data)
{
	if (x < data->width - 1)
	{
		data->x = x;
		data->y = y;
		data->y1 = y;
		data->x1 = x + 1;
		ft_brezenham(data);
	}
	if (y < data->height - 1)
	{
		data->x = x;
		data->y = y;
		data->x1 = x;
		data->y1 = y + 1;
		ft_brezenham(data);
	}
}

static void	draw_img(t_fdf *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < data->height)
	{
		x = -1;
		while (++x < data->width)
			draw_loop_body(x, y, data);
	}
}

void draw_scene(t_fdf *data)
{
	if (data->img->img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->img->img_ptr);
	data->img->img_ptr = mlx_new_image(data->mlx_ptr,
			data->img->img_width,
			data->img->img_height);
	draw_img(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img->img_ptr, 0, 0);
}
