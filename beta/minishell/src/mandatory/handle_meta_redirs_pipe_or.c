/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_meta_redirs_pipe_or.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 09:17:46 by dzuiev            #+#    #+#             */
/*   Updated: 2024/04/26 09:17:46 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_greater_than_sign(t_env **env, char **input)
{
	char	*start;

	start = *input;
	if (*(start + 1) == '>')
	{
		(*input)++;
		add_token(TOKEN_REDIR_APPEND, ft_strdup(">>"),
			ft_isspace(*(*input + 1)), env);
	}
	else
		add_token(TOKEN_REDIR_OUTPUT, ft_strdup(">"),
			ft_isspace(*(*input + 1)), env);
	(*input)++;
}

void	handle_less_than_sign(t_env **env, char **input)
{
	char	*start;

	start = *input;
	if (*(start + 1) == '<')
	{
		(*input)++;
		add_token(TOKEN_HERE_DOC, ft_strdup("<<"),
			ft_isspace(*(*input + 1)), env);
	}
	else
		add_token(TOKEN_REDIR_INPUT, ft_strdup("<"),
			ft_isspace(*(*input + 1)), env);
	(*input)++;
}

void	handle_pipe_or(t_env **env, char **input)
{
	char	*start;

	start = *input;
	if (*(start + 1) == '|')
	{
		(*input)++;
		add_token(TOKEN_OR_IF, ft_strdup("||"),
			ft_isspace(*(*input + 1)), env);
	}
	else
		add_token(TOKEN_PIPE, ft_strdup("|"),
			ft_isspace(*(*input + 1)), env);
	(*input)++;
}

void	handle_and(t_env **env, char **input)
{
	char	*start;

	start = *input;
	if (*(start + 1) == '&')
	{
		(*input)++;
		add_token(TOKEN_AND_IF, ft_strdup("&&"),
			ft_isspace(*(*input + 1)), env);
	}
	else
		add_token(TOKEN_BACKGROUND, ft_strdup("&"),
			ft_isspace(*(*input + 1)), env);
	(*input)++;
}
