/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:09:34 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/12 20:11:35 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libfdf.h"

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

void put_pixel_to_img(char *buffer, t_fdf *data, t_line *line)
{
	int	pixel_position;

	if (line->x >= 0 && line->x < data->img->img_width && line->y >= 0 && line->y < data->img->img_height) 
	{
		pixel_position = line->y * data->img->line_length + line->x * (data->img->bits_per_pixel / 8);
		*(unsigned int *)(buffer + pixel_position) = mlx_get_color_value(data->mlx_ptr, line->color);
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

void	init_line(t_line *line, t_fdf *data)
{
	line->x = data->x;
	line->y = data->y;
	line->x1 = data->x1;
	line->y1 = data->y1;
	line->length = 0;
	line->t = 0;
	line->dx = abs(line->x1 - line->x);
	if (line->x < line->x1)
		line->sx = 1;
	else
		line->sx = -1;
	line->dy = abs(line->y1 - line->y);
	if (line->y < line->y1)
		line->sy = 1;
	else
		line->sy = -1;
	line->err = line->dx - line->dy;
	line->length = sqrt(line->dx*line->dx + line->dy*line->dy);
}

static void draw_line(t_fdf *data, t_line *line)
{
	init_line(line, data);
	while (1)
	{
		if (data->z_color != data->z1_color)
		{
			line->t = sqrt((line->x1 - line->x)*(line->x1 - line->x) + (line->y1 - line->y)*(line->y1 - line->y)) / line->length;
			line->color = get_gradient_color(data->z_color, data->z1_color, line->t);
		}
		put_pixel_to_img(data->img->img_pixel_ptr, data, line);
		if (line->x == line->x1 && line->y == line->y1)
			break;
		line->e2 = 2 * line->err;
		if (line->e2 >= line->dy)
		{
			line->err += line->dy; // увеличиваем ошибку
			data->x += line->sx; // перемещаемся по оси X
		}
		if (line->e2 <= line->dx)
		{
			line->err += line->dx; // увеличиваем ошибку
			line->y += line->sy; // перемещаемся по оси Y
		}
	}
}

static void	ft_brezenham(t_fdf *data)
{
	data->z = data->my_map[(int)data->y][(int)data->x][0];
	data->z1 = data->my_map[(int)data->y1][(int)data->x1][0];
	data->z_color = data->my_map[(int)data->y][(int)data->x][1];
	data->z1_color = data->my_map[(int)data->y1][(int)data->x1][1];
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
	data->x+= data->shift_x;
	data->y+= data->shift_y;
	data->x1+= data->shift_x;
	data->y1+= data->shift_y;
	draw_line(data, data->line_struct);
}

static void	draw_img(t_fdf *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < data->height)
	{
		data->y = y;
		x = -1;
		while (++x < data->width)
		{
			data->x = x;
			if (x < data->width - 1)
			{
				data->x1 = x + 1;
				ft_brezenham(data);
			}
			if (y < data->height - 1)
			{
				data->y1 = y + 1;
				ft_brezenham(data);
			}
		}
	}
}

void draw_scene(t_fdf *data)
{
	clear_image_buffer(data->img);
	draw_img(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img->img_ptr, 0, 0);
}
