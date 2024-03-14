/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:39:07 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/14 13:10:07 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libfdf.h"

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
	draw_scene(data);
	handle_user_communication(data);
	mlx_loop(data->mlx_ptr);
	cleanup(data, img, NULL, 0);
	return (0);
}
