/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:31:56 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/14 13:29:28 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libfdf.h"

// Функция для отрисовки линий
static void	draw_loop_body(int x, int y, t_fdf *data)
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

// Функция для отрисовки изображения
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

// Функция для отрисовки сцены
void	draw_scene(t_fdf *data)
{
	if (data->img->img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->img->img_ptr);
	data->img->img_ptr = mlx_new_image(data->mlx_ptr,
			data->img->img_width,
			data->img->img_height);
	draw_img(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img->img_ptr, 0, 0);
}
