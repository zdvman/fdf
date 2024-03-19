/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 20:38:23 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/15 13:50:36 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libfdf.h"

static void	key_options(int keycode, t_fdf *data)
{
	if (keycode == XK_m)
		data->shift_index += 1;
	if (keycode == XK_n)
	{
		if (data->shift_index > 1)
			data->shift_index -= 1;
	}
	if (keycode == XK_v)
		data->z_zoom_index += 1;
	if (keycode == XK_b)
	{
		if (data->z_zoom_index > 1)
			data->z_zoom_index -= 1;
	}
}

// Функция для обработки нажатия клавиш
int	key_press_hook(int keycode, t_fdf *data)
{
	data->key_states[keycode] = 1;
	key_options(keycode, data);
	if (keycode == XK_g)
	{
		if (data->grad_flag)
			data->grad_flag = 0;
		else
			data->grad_flag = 1;
	}
	if (keycode == XK_x)
		data->res_step += 1;
	if (keycode == XK_z)
	{
		if (data->res_step > 1)
			data->res_step -= 1;
	}
	return (0);
}

// Функция для обработки отпускания клавиш
int	key_release_hook(int keycode, t_fdf *data)
{
	data->key_states[keycode] = 0;
	return (0);
}

// Функция для обработки нажатия клавиш
static void	key_angle_and_shift(t_fdf *data)
{
	if (data->key_states[XK_a])
		data->angle_y += data->angle_step;
	if (data->key_states[XK_d])
		data->angle_y -= data->angle_step;
	if (data->key_states[XK_w])
		data->angle_x += data->angle_step;
	if (data->key_states[XK_s])
		data->angle_x -= data->angle_step;
	if (data->key_states[XK_q])
		data->angle_z += data->angle_step;
	if (data->key_states[XK_e])
		data->angle_z -= data->angle_step;
	if (data->key_states[XK_Page_Up])
		data->zoom += 1.1;
	if (data->key_states[XK_Page_Down])
		data->zoom /= 1.0001;
	if (data->key_states[XK_Left])
		data->shift_x -= 1 * data->shift_index;
	if (data->key_states[XK_Right])
		data->shift_x += 1 * data->shift_index;
	if (data->key_states[XK_Up])
		data->shift_y -= 1 * data->shift_index;
	if (data->key_states[XK_Down])
		data->shift_y += 1 * data->shift_index;
}

// Функция для обработки состояний клавиш
int	handle_key_states(t_fdf *data)
{
	key_angle_and_shift(data);
	if (data->key_states[XK_Escape])
	{
		mlx_loop_end(data->mlx_ptr);
		return (0);
	}
	draw_scene(data);
	return (0);
}
