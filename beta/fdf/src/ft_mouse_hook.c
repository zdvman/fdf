/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mouse_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 20:37:46 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/11 20:38:08 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libfdf.h"

int	mouse_press(int button, int x, int y, t_fdf *data)
{
	(void)x;
	(void)y;
	if (button == 1)
		data->key_states[1] = 1;
	else if (button == 3)
	{
		data->last_x = x;
		data->last_y = y;
		data->key_states[3] = 1;
	}
	else if (button == 4)
	{
		data->zoom += 1.001;
		draw_scene(data);
	}
	else if (button == 5)
	{
		data->zoom -= 0.001;
		draw_scene(data);
	}
	return (0);
}

int	mouse_release(int button, int x, int y, t_fdf *data)
{
	(void)x;
	(void)y;
	if (button == 1)
		data->key_states[1] = 0;
	else if (button == 3)
		data->key_states[3] = 0;
	return (0);
}

int	mouse_move(int x, int y, t_fdf *data)
{
	if (data->key_states[1])
	{
		data->angle_x += (y - data->win_height / 2) * 0.0001;
		data->angle_y += (x - data->win_width / 2) * 0.0001;
		draw_scene(data);
	}
	if (data->key_states[3])
	{
		data->shift_x += (x - data->last_x) * 0.01;
		data->shift_y += (y - data->last_y) * 0.01;
		draw_scene(data);
	}
	return (0);
}
