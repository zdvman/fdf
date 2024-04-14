/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_and_project.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:52:10 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/18 19:53:35 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libfdf.h"

// Функция для поворота по оси X
static void	rotate_x(float *y, float *z, float angle)
{
	float	tmp_y;
	float	tmp_z;

	tmp_y = *y;
	tmp_z = *z;
	*y = tmp_y * cos(angle) - tmp_z * sin(angle);
	*z = tmp_y * sin(angle) + tmp_z * cos(angle);
}

// Функция для поворота по оси Y
static void	rotate_y(float *x, float *z, float angle)
{
	float	tmp_x;
	float	tmp_z;

	tmp_x = *x;
	tmp_z = *z;
	*x = tmp_x * cos(angle) + tmp_z * sin(angle);
	*z = -tmp_x * sin(angle) + tmp_z * cos(angle);
}

// Функция для поворота по оси Z
static void	rotate_z(float *x, float *y, float angle)
{
	float	tmp_x;
	float	tmp_y;

	tmp_x = *x;
	tmp_y = *y;
	*x = tmp_x * cos(angle) - tmp_y * sin(angle);
	*y = tmp_x * sin(angle) + tmp_y * cos(angle);
}

// Функция для проекции из 3D в 2D
static void	project(float *x, float *y, float z)
{
	float	iso_x;
	float	iso_y;

	iso_x = *x - z;
	iso_y = *y - z / 2;
	*x = iso_x;
	*y = iso_y;
}

// Функция для поворота и проекции
void	rotate_and_project(int *x, int *y, int *z, t_fdf *data)
{
	float	x_float;
	float	y_float;
	float	z_float;

	x_float = *x - data->center_x;
	y_float = *y - data->center_y;
	z_float = *z - data->center_z;
	rotate_x(&y_float, &z_float, data->angle_x);
	rotate_y(&x_float, &z_float, data->angle_y);
	rotate_z(&x_float, &y_float, data->angle_z);
	x_float += data->center_x;
	y_float += data->center_y;
	z_float += data->center_z;
	project(&x_float, &y_float, z_float);
	*x = ft_round(x_float);
	*y = ft_round(y_float);
}
