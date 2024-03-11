#include "../includes/libfdf.h"

// static float	ft_max(float a, float b)
// {
// 	if (a > b)
// 		return (a);
// 	return (b);
// }

// static float ft_abs(float a)
// {
// 	if (a < 0)
// 		return (-a);
// 	return (a);
// }

void rotate(float *x, float *y, float *z, t_fdf *data)
{
	// Rotate around the x-axis
	float tmp_y = *y;
	*y = cos(data->angle_x) * tmp_y - sin(data->angle_x) * (*z);
	*z = sin(data->angle_x) * tmp_y + cos(data->angle_x) * (*z);

	// Rotate around the y-axis
	float tmp_x = *x;
	*x = cos(data->angle_y) * tmp_x + sin(data->angle_y) * (*z);
	*z = -sin(data->angle_y) * tmp_x + cos(data->angle_y) * (*z);
}

void isometric_projection(int *iso_x, int *iso_y, float x, float y, float z)
{
	*iso_x = (int)(sqrt(2) / 2 * (x - z));
	*iso_y = (int)(sqrt(2) / 6 * y - (1 / sqrt(6)) * (x + z));
}

void put_pixel_to_img(char *buffer, int x, int y, int color, t_fdf *data)
{
	int pixel_position;

	if (x >= 0 && x < data->img->img_width && y >= 0 && y < data->img->img_height) 
	{
		pixel_position = y * data->img->line_length + x * (data->img->bits_per_pixel / 8);
		*(unsigned int *)(buffer + pixel_position) = mlx_get_color_value(data->mlx_ptr, color);
	}
}


void clear_image_buffer(t_img *img)
{
	int x;
	int y;

	y = 0;
	while (y < img->img_height)
	{
		x = 0;
		while (x < img->img_width)
		{
			int pixel_position = y * img->line_length + x * (img->bits_per_pixel / 8);
			*(unsigned int *)(img->img_pixel_ptr + pixel_position) = 0x000000;
			x++;
		}
		y++;
	}
}

// void clear_image_buffer(t_img *img)
// {
// 	int	i;
// 	int	total_pixels;

// 	i = 0;
// 	total_pixels = img->line_length * img->img_width / (img->bits_per_pixel / 8);
// 	while (i < total_pixels)
// 	{
// 		((int *)(img->img_pixel_ptr))[i] = 0x000000; // Assuming the pixel buffer is tightly packed
// 		i++;
// 	}
// }
void draw_scene(t_fdf *data)
{
	// Clear the window and the image buffer before redrawing
	clear_image_buffer(data->img);
	data->tile_width = data->img->img_width / data->width;
	data->tile_height = data->img->img_height / data->height;
	for (int i = 0; i < data->height; i++)
	{
		for (int j = 0; j < data->width; j++)
		{
			// Get your x, y, z values from your map data
			float x = j * data->tile_width;   // tile_width is the width of a tile in your map
			float y = i * data->tile_height;  // tile_height is the height of a tile
			float z = data->my_map[i][j];	 // Your z value from the map data

			// Rotate the point
			rotate(&x, &y, &z, data);

			// Apply isometric projection
			int iso_x, iso_y;
			isometric_projection(&iso_x, &iso_y, x, y, z);

			iso_x += data->shift_x;
			iso_y += data->shift_y;

			// Translate the point to the center of the screen or your preferred position
			iso_x += data->img->img_width / 2;
			iso_y += data->img->img_height / 2;

			// Draw the point on the image buffer
			put_pixel_to_img(data->img->img_pixel_ptr, iso_x, iso_y, data->color, data);
		}
	}

	// Place the image on the window
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img->img_ptr, 0, 0);
}


// void isometric(float *x, float *y, int z, t_fdf *data)
// {

// 	*iso_x = (int)(sqrt(2) / 2 * (x - z));
// 	*iso_y = (int)(sqrt(2) / 6 * y - (1 / sqrt(6)) * (x + z));


// 	// float x_temp = *x;
// 	// float y_temp = *y;

// 	*x *= data->zoom;
// 	*y *= data->zoom;
// 	// *z *= data->zoom;
// 	*x = (*x - *y) * cos(data->angle_x);
// 	z = z * data->zoom + *y * sin(data->angle_x)
// 		- z * cos(data->angle_x) * data->zoom;
// 	*y = (*x + *y) * sin(data->angle_y) - z * cos(data->angle_y);


// 	// *y = (*x + *y) * sin(0.8) - *z;
// 	// Rotate around the x-axis
// 	// *y = y_temp * cos(data->angle_x) + *z * sin(data->angle_x);
// 	// *z = -y_temp * sin(data->angle_x) + *z * cos(data->angle_x);

// 	// // Rotate around the y-axis
// 	// *x = x_temp * cos(data->angle_y) + *z * sin(data->angle_y);
// 	// // z is not used for the following calculations, but you can include this if needed:
// 	// *z = -x_temp * sin(data->angle_y) + *z * cos(data->angle_y);
	

// 	// Translate points to the center of the window or apply any other transformations needed
// 	*x += data->win_width / 2 - data->width * data->zoom / 2;
// 	*y += data->win_height / 2 - data->height * data->zoom / 2;
// }



// void ft_breseham(float x, float y, float x1, float y1, t_fdf *data)
// {
// 	float	x_step;
// 	float	y_step;
// 	int		max;
// 	int		z;
// 	int		z1;

// 	z = data->my_map[(int)y][(int)x];
// 	z1 = data->my_map[(int)y1][(int)x1];
// 	isometric(&x, &y, z, data);
// 	isometric(&x1, &y1, z1, data);
// 	x += data->shift_x;
// 	y += data->shift_y;
// 	x1 += data->shift_x;
// 	y1 += data->shift_y;
// 	// printf("%u\n", get_gradient_color(z, z1, data->max_z));
// 	x_step = x1 - x;
// 	y_step = y1 - y;
// 	max = ft_max(ft_abs(x_step), ft_abs(y_step));
// 	x_step /= max;
// 	y_step /= max;
// 	if (z || z1)
// 		data->color = 0xFF0000;
// 	else
// 		data->color = 0xFFFFFF;
// 	while ((int)(x - x1) || (int)(y - y1))
// 	{
// 		put_pixel_to_img(data->img->img_pixel_ptr, x, y, data->color, data);
// 		x += x_step;
// 		y += y_step;
// 	}
// }


// void draw_scene(t_fdf *data)
// {
// 	int y;
// 	int x;

// 	clear_image_buffer(data->img);
// 	y = 0;
// 	while (y < data->height)
// 	{
// 		x = 0;
// 		while (x < data->width)
// 		{
// 			if (x < data->width - 1)
// 				ft_breseham(x, y, x + 1, y, data);
// 			if (y < data->height - 1)
// 				ft_breseham(x, y, x, y + 1, data);
// 			x++;
// 		}
// 		y++;
// 	}
// 	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img->img_ptr, 0, 0);
// }
