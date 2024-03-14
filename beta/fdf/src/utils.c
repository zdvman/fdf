/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:31:39 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/07 12:31:39 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libfdf.h"

void	ft_error(char *error_msg, int exit_code)
{
	ft_putstr_fd(error_msg, STDERR_FILENO);
	exit(exit_code);
}

void	open_file(t_fdf *data, t_img *img, char *file, int flag)
{
	if (flag == 0)
		data->fd = open(file, O_RDONLY, 0644);
	else if (flag == 1)
		data->fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (flag == 2)
		data->fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (data->fd < 0)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		cleanup(data, img, NULL, 1);
	}
}

int	close_window(void *param)
{
	t_fdf	*data;

	data = (t_fdf *)param;
	mlx_loop_end(data->mlx_ptr);
	return (0);
}

void	open_window(t_fdf *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		cleanup(data, NULL, "Error: mlx_init() failed\n", 1);
	mlx_get_screen_size(data->mlx_ptr,
		&data->win_width,
		&data->win_height);
	data->win_ptr = mlx_new_window(data->mlx_ptr,
			data->win_width,
			data->win_height, "FDF");
	if (data->win_ptr == NULL)
		cleanup(data, NULL, "Error: mlx_new_window() failed\n", 1);
	data->shift_x = data->win_width / 2 - data->width * data->zoom / 2;
	data->shift_y = data->win_height / 2 - data->height * data->zoom / 2;
	data->img->img_width = data->win_width;
	data->img->img_height = data->win_height;
	data->img->img_ptr = mlx_new_image(data->mlx_ptr,
			data->img->img_width,
			data->img->img_height);
	if (data->img->img_ptr == NULL)
		cleanup(data, data->img, "Error: mlx_new_image() failed\n", 1);
	data->img->img_pixel_ptr = mlx_get_data_addr(data->img->img_ptr,
			&data->img->bits_per_pixel,
			&data->img->line_length,
			&data->img->endian);
}

void	handle_user_communication(t_fdf *data)
{
	mlx_hook(data->win_ptr, 4,
		1L << 2, mouse_press, data);
	mlx_hook(data->win_ptr, 5,
		1L << 3, mouse_release, data);
	mlx_hook(data->win_ptr, 6, 1 << 6, mouse_move, data);
	mlx_hook(data->win_ptr, 2, 1L << 0, key_press_hook, data);
	mlx_hook(data->win_ptr, 3, 1L << 1, key_release_hook, data);
	mlx_hook(data->win_ptr, 17, 0, close_window, data);
	mlx_loop_hook(data->mlx_ptr, &handle_key_states, data);
	mlx_loop(data->mlx_ptr);
}
