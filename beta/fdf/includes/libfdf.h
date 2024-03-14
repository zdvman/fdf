/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libfdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:19:21 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/14 14:43:43 by dzuiev           ###   ########.fr       */
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
# include <X11/X.h>
# include <X11/keysym.h>
# include <X11/Xlib.h>

/* ************************************************************************** */
/*                                                                            */
/*    Для использования функций из Libft необходимо включить                  */
/*    заголовочный файл "../libft/libft.h".                                   */
/*                                                                            */
/* ************************************************************************** */

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

# ifndef ANGLE_STEP
#  define ANGLE_STEP 0.035
# endif

typedef struct s_line
{
	int		x;
	int		y;
	int		x1;
	int		y1;
	int		dx;
	int		dy;
	int		sx;
	int		sy;
	int		err;
	int		e2;
	int		color;
	float	length;
	float	t;

}				t_line;

typedef struct s_img
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
	int		x;
	int		x1;
	int		y;
	int		y1;
	int		z;
	int		z1;
	int		z_color;
	int		z1_color;
	int		*key_states;
	int		width;
	int		height;
	int		win_width;
	int		win_height;
	int		zoom;
	int		color;
	int		shift_x;
	int		shift_y;
	int		last_x;
	int		last_y;
	float	angle_x;
	float	angle_y;
	float	angle_z;
	int		fd;
	char	*line;
	int		***my_map;
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	*img;
	t_line	*line_struct;
}				t_fdf;

// init.c
void			init_default(t_fdf *data, t_img *img, t_line *line);

// read_map.c
void			read_map(char *file, t_fdf *data, t_img *img);

// draw_scene.c
void			draw_scene(t_fdf *data);

// draw_line.c
void			ft_brezenham(t_fdf *data);

// rotate_and_project.c
void			rotate_and_project(int *x, int *y, int *z, t_fdf *data);

// mouse and keyboard hooks
int				key_press_hook(int keycode, t_fdf *data);
int				key_release_hook(int keycode, t_fdf *data);
int				handle_key_states(t_fdf *data);
int				mouse_press(int button, int x, int y, t_fdf *data);
int				mouse_release(int button, int x, int y, t_fdf *data);
int				mouse_move(int x, int y, t_fdf *data);

// gradient color
unsigned int	get_gradient_color(unsigned int startColor,
					unsigned int endColor, float t);

// ft_free_utils.c
void			cleanup(t_fdf *data, t_img *img,
					char *error_msg, int exit_code);
void			ft_free_3d_array(void ****array);
void			ft_free_array(void ***array);
void			ft_free_ptr(void **ptr);

// utils.c
void			ft_error(char *error_msg, int exit_code);
void			handle_user_communication(t_fdf *data);
void			open_file(t_fdf *data, t_img *img, char *file, int flag);
void			open_window(t_fdf *data);
int				close_window(void *param);

#endif
