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

void ft_free_ptr(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	cleanup(t_fdf *data, t_img *img, char *error_msg, int exit_code)
{
	if (data->fd >= 0)
		close(data->fd);
	if (data->line)
		ft_free_ptr((void **)&(data->line));
	if (data->my_map)
		ft_free_array((void ***)&(data->my_map));
	if (data->mlx_ptr)
	{
		if (data->win_ptr)
		{
			if (data->img->img_ptr)
			{
				mlx_destroy_image(data->mlx_ptr, data->img->img_ptr);
				data->img->img_ptr = NULL;
			}
			mlx_destroy_window(data->mlx_ptr, data->win_ptr);
			data->win_ptr = NULL;
		}
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		data->mlx_ptr = NULL;
	}
	if (img)
		ft_free_ptr((void **)&img);
	if (data)
		ft_free_ptr((void **)&data);
	if (exit_code)
		ft_error(error_msg, exit_code);
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

void	ft_free_array(void ***array)
{
	int	i;

	if (!*array)
		return ;
	i = 0;
	while ((*array)[i])
	{
		free((*array)[i]);
		i++;
	}
	free(*array);
	*array = NULL;
}
