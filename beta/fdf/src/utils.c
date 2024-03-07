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

void	cleanup(t_fdf *fdf, char *error_msg, int exit_code)
{
	if (fdf->fd >= 0)
		close(fdf->fd);
	if (fdf->line)
		ft_free_ptr((void **)&(fdf->line));
	if (fdf->mlx_ptr)
	{
		mlx_destroy_display(fdf->mlx_ptr);
		ft_free_ptr((void **)&(fdf->mlx_ptr));
	}
	if (fdf->win_ptr)
	{
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
		ft_free_ptr((void **)&(fdf->win_ptr));
	}
	if (fdf->my_map)
		ft_free_array((void ***)&(fdf->my_map));
	if (exit_code)
		ft_error(error_msg, exit_code);
}

void	open_file(t_fdf *fdf, char *file, int flag)
{
	if (flag == 0)
		fdf->fd = open(file, O_RDONLY, 0644);
	else if (flag == 1)
		fdf->fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (flag == 2)
		fdf->fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fdf->fd < 0)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		cleanup(fdf, NULL, 1);
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
