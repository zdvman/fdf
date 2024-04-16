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

int	is_special_character(char c)
{
	return (c == '<' || c == '>' || c == '|' || c == '&' || c == ';' || c == '(' || c == ')');
}

void	handle_greater_than_sign(t_token **tokens, char **input)
{
	char *start;

	start = *input;
	if (*(start + 1) == '>')
	{
		(*input)++;
		add_token(TOKEN_REDIR_APPEND, ft_strdup(">>"), tokens);
	}
	else
		add_token(TOKEN_REDIR_OUTPUT, ft_strdup(">"), tokens);
	(*input)++;
}

void	handle_less_than_sign(t_token **tokens, char **input)
{
	char *start;

	start = *input;
	if (*(start + 1) == '<')
	{
		(*input)++;
		add_token(TOKEN_HERE_DOC, ft_strdup("<<"), tokens);
	}
	else
		add_token(TOKEN_REDIR_INPUT, ft_strdup("<"), tokens);
	(*input)++;
}

void	handle_pipe_or(t_token **tokens, char **input)
{
	char *start;

	start = *input;
	if (*(start + 1) == '|')
	{
		(*input)++;
		add_token(TOKEN_OR, ft_strdup("||"), tokens);
	}
	else
	add_token(TOKEN_PIPE, ft_strdup("|"), tokens);
	(*input)++;
}

void	handle_and(t_token **tokens, char **input)
{
	char *start;

	start = *input;
	if (*(start + 1) == '&')
	{
		(*input)++;
		add_token(TOKEN_AND, ft_strdup("&&"), tokens);
	}
	(*input)++;
}

void	handle_semicolon(t_token **tokens, char **input)
{
	add_token(TOKEN_SEMI, ft_strdup(";"), tokens);
	(*input)++;
}

void	handle_open_bracket(t_token **tokens, char **input)
{
	add_token(TOKEN_OPEN_BRACKET, ft_strdup("("), tokens);
	(*input)++;
}

void	handle_close_bracket(t_token **tokens, char **input)
{
	add_token(TOKEN_CLOSE_BRACKET, ft_strdup(")"), tokens);
	(*input)++;
}
