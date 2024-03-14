/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_and_project.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:52:10 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/14 13:25:50 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libfdf.h"

// Функция для поворота по оси X
static void	rotate_x(int *y, int *z, float angle)
{
	float	tmp_y;
	float	tmp_z;

	tmp_y = *y;
	tmp_z = *z;
	*y = tmp_y * cos(angle) - tmp_z * sin(angle);
	*z = tmp_y * sin(angle) + tmp_z * cos(angle);
}

// Функция для поворота по оси Y
static void	rotate_y(int *x, int *z, float angle)
{
	float	tmp_x;
	float	tmp_z;

	tmp_x = *x;
	tmp_z = *z;
	*x = tmp_x * cos(angle) + tmp_z * sin(angle);
	*z = -tmp_x * sin(angle) + tmp_z * cos(angle);
}

// Функция для поворота по оси Z
static void	rotate_z(int *x, int *y, float angle)
{
	float	tmp_x;
	float	tmp_y;

	tmp_x = *x;
	tmp_y = *y;
	*x = tmp_x * cos(angle) - tmp_y * sin(angle);
	*y = tmp_x * sin(angle) + tmp_y * cos(angle);
}

// Функция для проекции из 3D в 2D
static void	project(int *x, int *y, int z)
{
	*x = ft_round((*x - z) * sqrt(3) / 2);
	*y = ft_round((*x + 2 * *y + z) / 2);
}

// Функция для поворота и проекции
void	rotate_and_project(int *x, int *y, int *z, t_fdf *data)
{
	rotate_x(y, z, data->angle_x);
	rotate_y(x, z, data->angle_y);
	rotate_z(x, y, data->angle_z);
	project(x, y, *z);
}
