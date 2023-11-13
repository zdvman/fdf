/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:02:31 by dzuiev            #+#    #+#             */
/*   Updated: 2023/11/13 15:51:54 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>
#include <fcntl.h>

int	main()
{
	int	fd;
	char	buf[256];
	int	chars_read;

	fd = open("file.txt", O_RDONLY);

	while (chars_read = read(fd, buf, 10))
	{
		buf[chars_read] = '\0';
		printf("buf: %s\n", buf);
	}

	// Open for reading only, if it's not exist - create a file.txt
	//fd = open("file.txt", O_RDONLY | O_CREAT);
	
	// Open to read and write, if it's not exist - create a file.txt
	//fd = open("file.txt", O_RDWR | O_CREAT);
	
	// ============================================
	// Open to read, write and append, if it's not exist - create a file.txt
	// When you use O_CREAT, you should also specify the file mode '0666'
	// The 0666 mode sets read and write permissions for the user, group, and others.
	// You can adjust these permissions as needed.
	//
	//fd = open("file.txt", O_RDWR | O_CREAT | O_APPEND);
	//=============================================
	
	//printf("fd of file %d\n", fd);
	
	//=============================================
	// The dup2(fd, 1); function call in your code is used to duplicate the 
	// file descriptor fd onto file descriptor 1, which is the file descriptor 
	// for standard output (stdout). Essentially, it's redirecting the standard 
	// output to the file represented by fd.
	// In simpler terms, after this call, anything that would normally be printed 
	// to the console (stdout) will instead be sent to the file associated with fd. 
	// This includes the output of printf, puts, and any other function 
	// that writes to stdout. In your case, it means the write(1, "hello", 5); 
	// line will write "hello" to file.txt instead of displaying it on the terminal.
	// However, it's important to note that this redirection will affect all standard 
	// output in the program after the dup2 call, not just the specific write call.
	
	//dup2(fd, 1);
	//=============================================
	
	//write(1, "hello", 5);
	//write(fd, "hello", 5);

	//puts("program running");
	//sleep(100);
	return (0);
}
