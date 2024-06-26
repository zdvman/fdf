/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:55:36 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/18 16:43:33 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libfdf.h"

// Функция для обработки событий и взаимодействия с пользователем
static void	handle_user_communication(t_fdf *data)
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

// Главная функция программы fdf с бонусами
int	main(int argc, char **argv)
{
	t_fdf	*data;
	t_img	*img;
	t_line	*line;

	if (argc != 2)
		ft_error("Argument error! Usage: ./data <existing_map.fdf>\n", 1);
	data = (t_fdf *)malloc(sizeof(t_fdf));
	img = (t_img *)malloc(sizeof(t_img));
	line = (t_line *)malloc(sizeof(t_line));
	if (img == NULL || data == NULL || line == NULL)
		cleanup(data, img, "Error: sructure malloc failed in main\n", 1);
	init_default(data, img, line);
	read_map(argv[1], data, img);
	open_window(data);
	get_zoom_and_center(data);
	draw_scene(data);
	handle_user_communication(data);
	cleanup(data, img, NULL, 0);
	return (0);
}
