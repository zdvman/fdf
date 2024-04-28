/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:17:27 by dzuiev            #+#    #+#             */
/*   Updated: 2024/04/28 13:56:05 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_free_tokens(t_token **tokens)
{
	t_token	*current;

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

static void ft_free_ast(t_ast_node **node)
{
	int	i;

	if (!*node)
		return ;
	i = 0;
	if ((*node)->args)
	{
		while ((*node)->args[i])
		{
			if ((*node)->args[i])
			{
				free((*node)->args[i]);
				(*node)->args[i] = NULL;
			}
			i++;
		}
		free((*node)->args);
		(*node)->args = NULL;
	}
	ft_free_ast(&(*node)->left);
	ft_free_ast(&(*node)->right);
	free(*node);
	*node = NULL;
}

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

void	ft_free_args(char ***args)
{
	int i;

	if (args == NULL || *args == NULL)
		return;
	i = 0;
	while ((*args)[i])
	{
		free((*args)[i]);
		(*args)[i] = NULL;
		i++;
	}
	free(*args);
	*args = NULL;
}

void	cleanup(t_env **env, int status)
{
	ft_free_tokens(&(*env)->tokens);
	ft_free_ast(&(*env)->ast);
	ft_free_env(env);
	rl_clear_history();
	printf("\033[?12l");
	if (status == EXIT_FAILURE)
		exit(status);
}
