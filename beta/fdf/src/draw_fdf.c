/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:09:34 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/11 20:56:19 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libfdf.h"

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	ft_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

void clear_image_buffer(t_img *img)
{
	ft_bzero(img->img_pixel_ptr, img->img_height * img->line_length);
}

void rotate(float *x, float *y, float *z, t_fdf *data)
{
	// Rotate around the x-axis
	float tmp_y = *y;
	*y = cos(data->angle_x) * tmp_y - sin(data->angle_x) * (*z);
	*z = sin(data->angle_x) * tmp_y + cos(data->angle_x) * (*z);

	// Rotate around the y-axis
	float tmp_x = *x;
	*x = cos(data->angle_y) * tmp_x + sin(data->angle_y) * (*z);
	*z = -sin(data->angle_y) * tmp_x + cos(data->angle_y) * (*z);
}

void isometric_projection(int *iso_x, int *iso_y, float x, float y, float z)
{
	*iso_x = (int)(sqrt(2) / 2 * (x - z));
	*iso_y = (int)(sqrt(2) / 6 * y - (1 / sqrt(6)) * (x + z));
}

void put_pixel_to_img(char *buffer, int x, int y, int color, t_fdf *data)
{
	int pixel_position;

	if (x >= 0 && x < data->img->img_width && y >= 0 && y < data->img->img_height) 
	{
		pixel_position = y * data->img->line_length + x * (data->img->bits_per_pixel / 8);
		*(unsigned int *)(buffer + pixel_position) = mlx_get_color_value(data->mlx_ptr, color);
	}
}

void rotate_and_project(float *x, float *y, float *z, t_fdf *data)
{
	// Временные переменные для хранения исходных значений
	float tmp_x = *x;
	float tmp_y = *y;
	float tmp_z = *z;
	// Вращение вокруг оси X
	*y = tmp_y * cos(data->angle_x) - tmp_z * sin(data->angle_x);
	*z = tmp_y * sin(data->angle_x) + tmp_z * cos(data->angle_x);
	tmp_y = *y;
	tmp_z = *z;
	// Вращение вокруг оси Y
	*x = tmp_x * cos(data->angle_y) + tmp_z * sin(data->angle_y);
	*z = -tmp_x * sin(data->angle_y) + tmp_z * cos(data->angle_y);
	tmp_x = *x;
	// Вращение вокруг оси Z (при необходимости)
	*x = tmp_x * cos(data->angle_z) - tmp_y * sin(data->angle_z);
	*y = tmp_x * sin(data->angle_z) + tmp_y * cos(data->angle_z);
	// Изометрическая проекция
	float iso_x = (*x - *z) * sqrt(3) / 2;
	float iso_y = (*x + 2 * *y + *z) / 2;
	// Возврат обновлённых значений
	*x = iso_x;
	*y = iso_y;
}

static void draw_line(int x, int y, int x1, int y1, t_fdf *data)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
	float length = sqrt(dx*dx + dy*dy);
	float progress, t;

	dx = abs(x1 - x);
	if (x < x1)
		sx = 1;
	else
		sx = -1;
	dy = abs(y1 - y);
	if (y < y1)
		sy = 1;
	else
		sy = -1;
	err = dx - dy;
	while (1)
	{
		put_pixel_to_img(data->img->img_pixel_ptr, x, y, data->color, data);
		if (x == x1 && y == y1)
			break;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy; // увеличиваем ошибку
			x += sx; // перемещаемся по оси X
		}
		if (e2 <= dx)
		{
			err += dx; // увеличиваем ошибку
			y += sy; // перемещаемся по оси Y
		}
	}
}

static void	ft_brezenham(float x, float y, float x1, float y1, t_fdf *data)
{
	float z;
	float z1;

	z = data->my_map[(int)y][(int)x][0];
	z1 = data->my_map[(int)y1][(int)x1][0];
	if (z || z1)
		data->color = 0xFF0000;
	else
		data->color = 0xFFFFFF;
	x *= data->zoom;
	y *= data->zoom;
	z *= data->zoom;
	x1 *= data->zoom;
	y1 *= data->zoom;
	z1 *= data->zoom;
	rotate_and_project(&x, &y, &z, data);
	rotate_and_project(&x1, &y1, &z1, data);
	x+= data->shift_x;
	y+= data->shift_y;
	x1+= data->shift_x;
	y1+= data->shift_y;
	draw_line(x, y, x1, y1, data);
}


void draw_scene(t_fdf *data)
{
	int y;
	int x;

	clear_image_buffer(data->img);
	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (x < data->width - 1)
				ft_brezenham(x, y, x + 1, y, data);
			if (y < data->height - 1)
				ft_brezenham(x, y, x, y + 1, data);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img->img_ptr, 0, 0);
}
