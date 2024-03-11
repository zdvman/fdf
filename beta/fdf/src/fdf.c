/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:39:07 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/10 11:58:33 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libfdf.h"

void open_window(t_fdf *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		cleanup(data, NULL, "Error: mlx_init() failed\n", 1);
	mlx_get_screen_size(data->mlx_ptr, &data->win_width, &data->win_height);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->win_width, data->win_height, "FDF");
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

// void clear_image_buffer(t_img *img)
// {
// 	int	x;
// 	int	y;

// 	y = 0;	
// 	// Assuming your image is 1920 pixels wide and 1080 pixels high
// 	while (y < img->img_height) // (1080)
// 	{
// 		x = 0;
// 		while (x < img->img_width) // (1920)
// 		{
// 			// Compute the position of the pixel
// 			int pixel_position = y * img->line_length + x * (img->bits_per_pixel / 8);
// 			// Set the pixel to black (color 0x000000)
// 			*(unsigned int *)(img->img_pixel_ptr + pixel_position) = 0x000000;
// 			x++;
// 		}
// 		y++;
// 	}
// }



int deal_key(int key, t_fdf *data)
{
	printf("Key: %d\n", key);
	if (key == 61) // Replace with the actual key code or mouse scroll event
		data->zoom *= 1.1; // Zoom in by 10%
	if (key == 45) // Replace with the actual key code or mouse scroll event
		data->zoom /= 1.1; // Zoom out by 10%
	if (key == 65362)
		data->angle_x -= ANGLE_STEP;
	if (key == 65364)
		data->angle_x += ANGLE_STEP;
	if (key == 65361)
		data->angle_y -= ANGLE_STEP;
	if (key == 65363)
		data->angle_y += ANGLE_STEP;
	if (key == 97)
		data->shift_x -= 10;
	if (key == 100)
		data->shift_x += 10;
	if (key == 119)
		data->shift_y -= 10;
	if (key == 115)
		data->shift_y += 10;
	if (key == 65307)
	{
		mlx_loop_end(data->mlx_ptr);
		return (0);
	}
	draw_scene(data);
	// mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img->img_ptr, 0, 0);
	return (0);
}

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
	// ft_mlx_pixel_put(img, 5, 5, 0x00FF0000);
	// mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	// mlx_hook(data->win_ptr, 2, 1L << 0, handle_input, data);
	mlx_key_hook(data->win_ptr, deal_key, data);
	mlx_loop(data->mlx_ptr);
	cleanup(data, img, NULL, 0);
	return (0);
}
