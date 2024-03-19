/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:13:50 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/19 09:14:03 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libphilo.h"

// Функция для освобождения 3D массива
void	ft_free_3d_array(void ****array)
{
	int	i;
	int	j;

	if (array == NULL || *array == NULL)
		return ;
	i = 0;
	while ((*array)[i])
	{
		j = 0;
		while ((*array)[i][j])
		{
			free((*array)[i][j]);
			j++;
		}
		free((*array)[i]);
		i++;
	}
	free(*array);
	*array = NULL;
}

// Функция для освобождения двумерного массива
void	ft_free_2d_array(void ***array)
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

// Функция для освобождения указателя
void	ft_free_ptr(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

// Функция для освобождения всей памяти и завершения программы
// void	cleanup(t_fdf *data, t_img *img, char *error_msg, int exit_code)
// {
// 	if (data->key_states)
// 		ft_free_ptr((void **)&(data->key_states));
// 	if (data->fd >= 0)
// 		close(data->fd);
// 	if (data->line)
// 		ft_free_ptr((void **)&(data->line));
// 	if (data->my_map)
// 		ft_free_3d_array((void ****)&(data->my_map));
// 	if (data->mlx_ptr)
// 		ft_destroy_mlx(data);
// 	if (img)
// 		ft_free_ptr((void **)&img);
// 	if (data->line_struct)
// 		ft_free_ptr((void **)&(data->line_struct));
// 	if (data)
// 		ft_free_ptr((void **)&data);
// 	if (exit_code)
// 		ft_error(error_msg, exit_code);
// }
