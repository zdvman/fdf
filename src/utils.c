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

// Функция для вывода сообщения об ошибке и выхода из программы
void	ft_error(char *error_msg, int exit_code)
{
	ft_putstr_fd(error_msg, STDERR_FILENO);
	exit(exit_code);
}

// Функция для очистки памяти и выхода из программы
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

// Функция для закрытия окна
int	close_window(void *param)
{
	t_fdf	*data;

	data = (t_fdf *)param;
	mlx_loop_end(data->mlx_ptr);
	return (0);
}

// Функция для инициализации структуры img
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
