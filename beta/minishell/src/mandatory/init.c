/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:42:01 by dzuiev            #+#    #+#             */
/*   Updated: 2024/04/24 20:36:39 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	env_init(t_env **env, char **envp, int env_len)
{
	int	i;

	(*env)->envp = malloc(sizeof(char *) * (env_len + 1));
	if ((*env)->envp == NULL)
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
	}
	(*env)->tokens = NULL;
	(*env)->head_token = NULL;
}

void	shell_init(t_env **env, char **envp)
{
	int	env_len;

	*env = malloc(sizeof(t_env));
	if (*env == NULL)
	{
		ft_perror("malloc failed\n");
		cleanup(env, EXIT_FAILURE);
	}
	env_len = ft_strarr_len(envp);
	env_init(env, envp, env_len);
	printf("\033[?12h");
	set_sig_actions();
}
