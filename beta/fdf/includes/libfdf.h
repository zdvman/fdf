/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libfdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:19:21 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/07 20:48:49 by dzuiev           ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*    Для использования функций из Libft необходимо включить                  */
/*    заголовочный файл "../libft/libft.h".                                   */
/*                                                                            */
/* ************************************************************************** */

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"


typedef struct s_fdf
{
	size_t	width;
	size_t	height;
	int		fd;
	char	*line;
	int		**my_map;
	void	*mlx_ptr;
	void	*win_ptr;
}				t_fdf;

void	init_default(t_fdf *fdf);
void	open_file(t_fdf *fdf, char *file, int flag);
void	read_map(char *file, t_fdf *fdf);
void	ft_error(char *error_msg, int exit_code);
void	cleanup(t_fdf *fdf, char *error_msg, int exit_code);
void	ft_free_array(void ***array);

#endif
