/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:17:27 by dzuiev            #+#    #+#             */
/*   Updated: 2024/04/19 18:33:23 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void ft_free_tokens(t_token **tokens)
{
	t_token *current;

	if (tokens == NULL || *tokens == NULL)
		return ;
	while (*tokens != NULL)
	{
		current = *tokens;
		*tokens = (*tokens)->next;
		if (current->value != NULL)
			free(current->value);
		free(current);
	}
	*tokens = NULL;
}

// Функция для освобождения двумерного массива
static void	ft_free_env(t_env **env)
{
	int	i;

	if (!*env)
		return ;
	i = 0;
	if ((*env)->envp)
	{
		while ((*env)->envp[i])
		{
			if ((*env)->envp[i])
			{
				free((*env)->envp[i]);
				(*env)->envp[i] = NULL;
			}
			i++;
		}
		free((*env)->envp);
		(*env)->envp = NULL;
	}
	free(*env);
}

void cleanup(t_env **env, int status)
{
	ft_free_tokens(&(*env)->token);
	ft_free_env(env);
	rl_clear_history();
	printf("\033[?12l");
	if (status == EXIT_FAILURE)
		exit(status);
}
