/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:39:07 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/11 20:43:45 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libfdf.h"

int	main(int argc, char **argv)
{
	t_fdf	*data;
	t_img	*img;

	if (argc != 2)
		ft_error("Argument error! Usage: ./data <existing_map.fdf>\n", 1);
	data = (t_fdf *)malloc(sizeof(t_fdf));
	img = (t_img *)malloc(sizeof(t_img));
	if (img == NULL || data == NULL)
		cleanup(data, img, "Error: sructure malloc failed in main\n", 1);
	init_default(data, img);
	read_map(argv[1], data, img);
	open_window(data);
	draw_scene(data);
	mlx_hook(data->win_ptr, 4, 1L<<2 , mouse_press, data);
	mlx_hook(data->win_ptr, 5, 1L<<3, mouse_release, data);
	mlx_hook(data->win_ptr, 6, 1<<6, mouse_move, data);
	mlx_hook(data->win_ptr, 2, 1L<<0, key_press_hook, data);
	mlx_hook(data->win_ptr, 3, 1L<<1, key_release_hook, data);
	mlx_hook(data->win_ptr, 17, 0, close_window, data);
	mlx_loop_hook(data->mlx_ptr, &handle_key_states, data);
	mlx_loop(data->mlx_ptr);
	cleanup(data, img, NULL, 0);
	return (0);
}
