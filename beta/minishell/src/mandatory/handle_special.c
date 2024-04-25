/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:32:43 by dzuiev            #+#    #+#             */
/*   Updated: 2024/04/15 13:32:43 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_meta_character(char c)
{
	return (c == '<'
		|| c == '>'
		|| c == '|'
		|| c == '&'
		|| c == ';'
		|| c == '('
		|| c == ')');
}

void	handle_greater_than_sign(t_env **env, char **input)
{
	char	*start;

	start = *input;
	if (*(start + 1) == '>')
	{
		(*input)++;
		add_token(TOKEN_REDIR_APPEND, ft_strdup(">>"), ft_isspace(*(*input + 1)), env);
	}
	else
		add_token(TOKEN_REDIR_OUTPUT, ft_strdup(">"), ft_isspace(*(*input + 1)), env);
	(*input)++;
}

void	handle_less_than_sign(t_env **env, char **input)
{
	char	*start;

	start = *input;
	if (*(start + 1) == '<')
	{
		(*input)++;
		add_token(TOKEN_HERE_DOC, ft_strdup("<<"), ft_isspace(*(*input + 1)), env);
	}
	else
		add_token(TOKEN_REDIR_INPUT, ft_strdup("<"), ft_isspace(*(*input + 1)), env);
	(*input)++;
}

void	handle_pipe_or(t_env **env, char **input)
{
	char	*start;

	start = *input;
	if (*(start + 1) == '|')
	{
		(*input)++;
		add_token(TOKEN_OR_IF, ft_strdup("||"), ft_isspace(*(*input + 1)), env);
	}
	else
		add_token(TOKEN_PIPE, ft_strdup("|"), ft_isspace(*(*input + 1)), env);
	(*input)++;
}

void	handle_and(t_env **env, char **input)
{
	char	*start;

	start = *input;
	if (*(start + 1) == '&')
	{
		(*input)++;
		add_token(TOKEN_AND_IF, ft_strdup("&&"), ft_isspace(*(*input + 1)), env);
	}
	else
		add_token(TOKEN_BACKGROUND, ft_strdup("&"), ft_isspace(*(*input + 1)), env);
	(*input)++;
}

void	handle_semicolon(t_env **env, char **input)
{
	add_token(TOKEN_SEMI, ft_strdup(";"), ft_isspace(*(*input + 1)), env);
	(*input)++;
}

void	handle_open_bracket(t_env **env, char **input)
{
	add_token(TOKEN_OPEN_BRACKET, ft_strdup("("), ft_isspace(*(*input + 1)), env);
	(*input)++;
}

void	handle_close_bracket(t_env **env, char **input)
{
	add_token(TOKEN_CLOSE_BRACKET, ft_strdup(")"), ft_isspace(*(*input + 1)), env);
	(*input)++;
}
