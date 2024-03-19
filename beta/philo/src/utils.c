/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:15:48 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/19 09:15:48 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libphilo.h"

void	ft_error(char *error_msg, int exit_code)
{
	ft_putstr_fd(error_msg, STDERR_FILENO);
	exit(exit_code);
}
