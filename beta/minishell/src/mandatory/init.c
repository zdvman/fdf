/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:42:01 by dzuiev            #+#    #+#             */
/*   Updated: 2024/04/19 19:00:05 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	tokens_init(t_token **tokens)
{
	*tokens = malloc(sizeof(t_token));
	(*tokens)->value = NULL;
	(*tokens)->next = NULL;
	(*tokens)->prev = NULL;
}

void env_init(t_env **env, char **envp, int env_len)
{
	int	i;

	*env = malloc(sizeof(t_env));
	(*env)->envp = malloc(sizeof(char *) * (env_len + 1));
	if (*env == NULL || (*env)->envp == NULL)
	{
		ft_perror("malloc failed\n");
		cleanup(env, EXIT_FAILURE);
	}
	(*env)->envp[env_len] = NULL;
	i = -1;
	while (envp[++i] != NULL)
	{
		(*env)->envp[i] = ft_strdup(envp[i]);
		if ((*env)->envp[i] == NULL)
		{
			ft_perror("malloc failed\n");
			cleanup(env, EXIT_FAILURE);
		}
		printf("%s\n", (*env)->envp[i]);
	}
	(*env)->token = NULL;
	(*env)->head_token = NULL;
}


void shell_init(t_env **env, t_token **tokens, char **envp)
{
	int	env_len;

	*tokens = malloc(sizeof(t_token));
	if (tokens == NULL)
	{
		ft_perror("malloc failed\n");
		cleanup(env, EXIT_FAILURE);
	}
	env_len = ft_strarr_len(envp);
	env_init(env, envp, env_len);
	tokens_init(tokens);
	printf("\033[?12h");
	set_sig_actions();
}
