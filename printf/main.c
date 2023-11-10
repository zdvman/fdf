/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:25:01 by dzuiev            #+#    #+#             */
/*   Updated: 2023/11/10 11:25:01 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		main(void)
{
	ft_printf("Hello %s, today is %d, in hex %x, char %c, and %%\n", "world", 20161109, 20161109, 'a');
	printf("Hello %s, today is %d, in hex %x, char %c, and %%\n", "world", 20161109, 20161109, 'a');
	return (0);
}
