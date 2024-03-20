/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:47:29 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/20 18:33:11 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libphilo.h"

static void	handle_thread_err(int status, t_data *data)
{
	if (status == 0)
		return ;
	else
		cleanup(data, RED"Thread error!\n"RST, 1);
}

void	ft_thread_handle(pthread_t *thread, void *(*func) (void *),
			t_opcode code, void *arg)
{
	if (code == CREATE)
		handle_thread_err(pthread_create(thread, NULL, func, arg), data);
	else if (data->code == JOIN)
		handle_thread_err(pthread_join(*thread, NULL), data);
	else if (data->code == DETACH)
		handle_thread_err(pthread_detach(*thread), data);
	else
		cleanup(data, RED"Wrong thread operation code!\n"RST, 1);
}
