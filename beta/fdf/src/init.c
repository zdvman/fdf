/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:00:16 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/07 19:00:16 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libfdf.h"

void	init_default(t_fdf *fdf)
{
	fdf->fd = -1;
	fdf->width = 0;
	fdf->height = 0;
	fdf->line = NULL;
	fdf->my_map = NULL;
	fdf->mlx_ptr = NULL;
	fdf->win_ptr = NULL;
}
