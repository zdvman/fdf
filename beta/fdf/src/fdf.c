/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:39:07 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/07 11:39:07 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libfdf.h"

int	main(int argc, char **argv)
{
	t_fdf	fdf;
	// int		i;

	// i = 0;
	if (argc != 2)
		ft_error("Argument error! Usage: ./fdf <existing_map.fdf>\n", 1);
	init_default(&fdf);
	read_map(argv[1], &fdf);
	fdf.mlx_ptr = mlx_init();
	if (fdf.mlx_ptr == NULL)
		cleanup(&fdf, "Error: mlx_init() failed\n", 1);
	fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, 1920, 1080, "FDF");
	if (fdf.win_ptr == NULL)
		cleanup(&fdf, "Error: mlx_new_window() failed\n", 1);
	mlx_loop(fdf.mlx_ptr);
	// printf("Width: %zu Height: %zu\n", fdf.width, fdf.height);
	// while (fdf.my_map[i] != NULL)
	// {
	// 	printf("x = %d; cos(x) = %f; y = %d; z = %d\n", fdf.my_map[i][0], cos(fdf.my_map[i][0]),
	// 		fdf.my_map[i][1], fdf.my_map[i][2]);
	// 	printf("\n");
	// 	i++;
	// }
	cleanup(&fdf, NULL, 0);
	return (0);
}
