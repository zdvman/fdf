/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 20:38:23 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/14 19:13:53 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libfdf.h"

// Функция для обработки нажатия клавиш
int	key_press_hook(int keycode, t_fdf *data)
{
	data->key_states[keycode] = 1;
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
		data->angle_y += ANGLE_STEP;
	if (data->key_states[XK_d])
		data->angle_y -= ANGLE_STEP;
	if (data->key_states[XK_w])
		data->angle_x += ANGLE_STEP;
	if (data->key_states[XK_s])
		data->angle_x -= ANGLE_STEP;
	if (data->key_states[XK_q])
		data->angle_z += ANGLE_STEP;
	if (data->key_states[XK_e])
		data->angle_z -= ANGLE_STEP;
	if (data->key_states[XK_Page_Up])
		data->zoom += 1.1;
	if (data->key_states[XK_Page_Down])
		data->zoom /= 1.0001;
	if (data->key_states[XK_Left])
		data->shift_x -= 1;
	if (data->key_states[XK_Right])
		data->shift_x += 1;
	if (data->key_states[XK_Up])
		data->shift_y -= 1;
	if (data->key_states[XK_Down])
		data->shift_y += 1;
}

// Функция для обработки состояний клавиш
int	handle_key_states(t_fdf *data)
{
	key_angle_and_shift(data);
	if (data->key_states[XK_g])
		data->grad_flag *= -1;
	if (data->key_states[XK_Escape])
	{
		mlx_loop_end(data->mlx_ptr);
		return (0);
	}
	draw_scene(data);
	return (0);
}
