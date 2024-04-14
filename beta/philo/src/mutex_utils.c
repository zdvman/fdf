/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:45:01 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/20 18:17:17 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libphilo.h"

static void	handle_mtx_err(int status, t_data *data)
{
	if (status == 0)
		return ;
	else
		cleanup(data, RED"Mutex error!\n"RST, 1);
}

void	ft_mutex_handle(t_mtx *mtx, t_opcode code, t_data *data)
{
	if (code == LOCK)
		handle_mtx_err(pthread_mutex_lock(mtx), data);
	else if (code == UNLOCK)
		handle_mtx_err(pthread_mutex_unlock(mtx), data);
	else if (code == INIT)
		handle_mtx_err(pthread_mutex_init(mtx, NULL), data);
	else if (code == DESTROY)
		handle_mtx_err(pthread_mutex_destroy(mtx), data);
	else
		cleanup(data, RED"Wrong mutex operation code!\n"RST, 1);
}
