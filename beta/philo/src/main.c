/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:04:15 by dzuiev            #+#    #+#             */
/*   Updated: 2024/04/08 16:19:10 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libphilo.h"

int credits(int n)
{
	n += 200;
	return (n);
}

void ft_process(void *n)
{
	*(int *)n = credits(*(int *)n);
	printf("%d\n", *(int *)n);
}


int main(void)
{
	int n = 100;
	pthread_t thread1;
	pthread_t thread2;

	pthread_create(&thread1, NULL, (void *)ft_process, (void *)&n);
	pthread_create(&thread2, NULL, (void *)ft_process, (void *)&n);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	printf("%d\n", n);
	return (0);
}
