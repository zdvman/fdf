/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:14:13 by dzuiev            #+#    #+#             */
/*   Updated: 2023/11/20 19:41:10 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Please input name of txt files: %s <name 1> <name 2> ...\n", argv[0]);
		return (1);
	}
	
	int *fds = malloc((argc - 1) * sizeof(int));
	int active_files = argc - 1;

	// Открываем все файлы и заполняем массив дескрипторов
	for (int i = 0; i < active_files; i++)
	{
		fds[i] = open(argv[i + 1], O_RDONLY);
		if (fds[i] == -1)
		{
			perror("Open file error");
			return (1);
		}
	}

	// Инициализация генератора случайных чисел
	srand(time(NULL));

	// Чтение строк из файлов в случайном порядке
	while (active_files > 0)
	{
		int random_index = rand() % active_files;
		char *line = get_next_line(fds[random_index]);

		if (line)
		{
			printf("%s", line);
			free(line);
			usleep(500000);
		}
		else
		{
			// Закрытие файла, если строки закончились
			close(fds[random_index]);
			fds[random_index] = fds[active_files - 1]; // Перемещаем последний активный файл на место закрытого
			active_files--;
		}
	}
	free(fds); // Освобождаем память
	return 0;
}

