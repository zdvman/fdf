/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_default.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:55:53 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/14 19:24:29 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libfdf.h"

static void	z_or_z1_not_zero(t_fdf *data)
{
	if (data->z > data->z1)
	{
		if (data->z_color == 0)
			data->z_color = 0x00C9FF;
		if (data->z1_color == 0)
			data->z1_color = 0xFF4E50;
	}
	else
	{
		if (data->z_color == 0)
			data->z_color = 0xFF4E50;
		if (data->z1_color == 0)
			data->z1_color = 0x00C9FF;
	}
}

static void	z_and_z1_not_zero_and_equal(t_fdf *data)
{
	if (data->z > 0)
	{
		if (data->z_color == 0)
			data->z_color = 0xFF4E50;
		if (data->z1_color == 0)
			data->z1_color = 0xFF4E50;
	}
	else
	{
		if (data->z_color == 0)
			data->z_color = 0x00C9FF;
		if (data->z1_color == 0)
			data->z1_color = 0x00C9FF;
	}
}

static void	z_and_z1_zero(t_fdf *data)
{
	if (data->z_color == 0)
		data->z_color = data->color;
	if (data->z1_color == 0)
		data->z1_color = data->color;
}

void	get_color_default(t_fdf *data)
{
	if ((data->z || data->z1) && data->z != data->z1)
		z_or_z1_not_zero(data);
	else if (data->z && data->z1 && data->z == data->z1)
		z_and_z1_not_zero_and_equal(data);
	else if (!(data->z && data->z1))
		z_and_z1_zero(data);
}
