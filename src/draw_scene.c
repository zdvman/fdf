/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:31:56 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/18 19:58:44 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libfdf.h"

// Функция для отрисовки линий
static void	draw_loop_body(int x, int y, t_fdf *data)
{
	if (x < data->width - data->res_step)
	{
		data->x = x;
		data->y = y;
		data->y1 = y;
		data->x1 = x + data->res_step;
		ft_brezenham(data);
	}
	if (y < data->height - data->res_step)
	{
		data->x = x;
		data->y = y;
		data->x1 = x;
		data->y1 = y + data->res_step;
		ft_brezenham(data);
	}
}

// Функция для отрисовки изображения
static void	draw_img(t_fdf *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			draw_loop_body(x, y, data);
			x++;
		}
		y++;
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
