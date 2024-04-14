/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:39:53 by dzuiev            #+#    #+#             */
/*   Updated: 2024/04/12 18:09:56 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/******************************************************************************/
/*                                Minishell                                   */
/* Project structure:                                                         */
/*  minishell/                                                                */
/* ├── libft/              # Libft library files                              */
/* │   ├── Makefile                                                           */
/* │   └── ...             # Libft source files and headers                   */
/* ├── src/                # Source files for Minishell                       */
/* │   ├── core/           # Core functionality for both parts                */
/* │   │   └── ...         # Core implementation files                        */
/* │   ├── mandatory/      # Mandatory specific files                         */
/* │   │   └── ...         # Mandatory implementation files                   */
/* │   ├── bonus/          # Bonus specific files (if any)                    */
/* │   │   └── ...         # Bonus implementation files                       */
/* │   └── main.c          # Main program entry point                         */
/* ├── includes/           # Header files                                     */
/* │   ├── minishell.h                                                        */
/* │   └── bonus_features.h                                                   */
/* ├── Makefile                                                               */
/* └── README.md                                                              */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"
#ifdef BONUS
#include "../includes/minishell_bonus.h" // Включается только при компиляции бонусной части
#endif

void	handle_sigint(int sig)
{
	(void)sig;
	write(STDIN_FILENO, "\nminishell> ", 12);
	fflush(stdout);
}

void	set_sig_actions(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	memset(&sa_int, 0, sizeof(sa_int));
	sa_int.sa_handler = handle_sigint;
	sigaction(SIGINT, &sa_int, NULL);
	memset(&sa_quit, 0, sizeof(sa_quit));
	sa_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

int	main(void)
{
	char	*input;

	printf("\033[?12h");
	set_sig_actions();
	input = NULL;
	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL)
		{
			printf("exit\n");
			printf("\033[?12l");
			break ;
		}
		if (input && *input)
		{
			add_history(input);
			// tokenize(input);
		}
		if (input)
			free(input);
	}
	printf("\033[?12l");
	rl_clear_history();
	return (0);
}
