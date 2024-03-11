/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libfdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:19:21 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/08 13:41:49 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFDF_H
# define LIBFDF_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <errno.h>
# include <math.h>
# include <string.h>
// # include <X11/X.h>
// # include <X11/keysym.h>
// # include <X11/Xlib.h>

/* ************************************************************************** */
/*                                                                            */
/*    Для использования функций из Libft необходимо включить                  */
/*    заголовочный файл "../libft/libft.h".                                   */
/*                                                                            */
/* ************************************************************************** */

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif
// # define ANGLE_STEP (M_PI / 360)  // This defines a step of 0.5 degrees.
# define ANGLE_STEP (M_PI / 90)  // This defines a step of 1 degree.

typedef struct	s_img
{
	void	*img_ptr;
	char	*img_pixel_ptr;
	int		bits_per_pixel;
	int		endian;
	int		line_length;
	int		img_width;
	int		img_height;
}				t_img;

typedef struct s_fdf
{
	int		width;
	int		height;
	int		tile_width;
	int		tile_height;
	int		win_width;
	int		win_height;
	int		zoom;
	int		color;
	int		max_z;
	int		shift_x;
	int		shift_y;
	float	angle_x;
	float	angle_y;
	int		fd;
	char	*line;
	int		**my_map;
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	*img;
}				t_fdf;

void	init_default(t_fdf *data, t_img *img);
void	open_file(t_fdf *data, t_img *img, char *file, int flag);
void	read_map(char *file, t_fdf *data, t_img *img);
void	ft_error(char *error_msg, int exit_code);
void	cleanup(t_fdf *data, t_img *img, char *error_msg, int exit_code);
void	ft_free_array(void ***array);
void	draw_scene(t_fdf *data);
void	ft_breseham(float x, float y, float x1, float y1, t_fdf *data);

#endif
