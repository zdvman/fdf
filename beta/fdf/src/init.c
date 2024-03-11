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

void	init_default(t_fdf *data, t_img *img)
{
	data->img = img;
	data->fd = -1;
	data->width = 0;
	data->height = 0;
	data->tile_width = 0;
	data->tile_height = 0;
	data->zoom = 40;
	data->color = 0xFF0000;
	data->max_z = 0;
	data->shift_x = 0;
	data->shift_y = 0;
	data->angle_x = 0;
	data->angle_y = 0;
	data->line = NULL;
	data->my_map = NULL;
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	img->img_ptr = NULL;
	img->img_pixel_ptr = NULL;
	img->bits_per_pixel = 0;
	img->endian = 0;
	img->line_length = 0;
}
