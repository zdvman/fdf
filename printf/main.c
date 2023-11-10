/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:25:01 by dzuiev            #+#    #+#             */
/*   Updated: 2023/11/10 17:54:01 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		main(void)
{
	char *ptr = "abc";


	ft_printf("str %s, digit %d, int %i, in hex %x, char %c, pointer %p, and %%\n",
			"world", -20161109, -201, 1000, 'c', ptr);
	printf("str %s, digit %d, int %i, in hex %x, char %c, pointer %p, and %%\n",
			"world", -20161109, -201, 1000, 'c', ptr);
	return (0);
}
