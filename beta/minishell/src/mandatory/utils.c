/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:26:28 by dzuiev            #+#    #+#             */
/*   Updated: 2024/04/15 11:26:28 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_sigint(int sig)
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
