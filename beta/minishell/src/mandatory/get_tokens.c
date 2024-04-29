/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 08:48:04 by dzuiev            #+#    #+#             */
/*   Updated: 2024/04/26 08:48:04 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_token(t_token_type type, char *value, int space_after, t_env **env)
{
	t_token	*token;
	t_token	*current;

	token = malloc(sizeof(t_token));
	if (token == NULL)
	{
		ft_perror("malloc failed\n");
		cleanup(env, EXIT_FAILURE);
	}
	token->type = type;
	token->value = value;
	token->has_space = space_after;
	token->next = NULL;
	if ((*env)->tokens == NULL)
		(*env)->tokens = token;
	else
	{
		current = (*env)->tokens;
		while (current->next != NULL)
			current = current->next;
		current->next = token;
	}
}

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

void	handle_meta(t_env **env, char **input)
{
	char	*current;

	current = *input;
	if (*current == '<')
		handle_less_than_sign(env, &current);
	else if (*current == '>')
		handle_greater_than_sign(env, &current);
	else if (*current == '|')
		handle_pipe_or(env, &current);
	else if (*current == '&')
		handle_and(env, &current);
	else if (*current == ';')
		handle_semicolon(env, &current);
	else if (*current == '(')
		handle_open_bracket(env, &current);
	else if (*current == ')')
		handle_close_bracket(env, &current);
	*input = current;
}

void	tokenize_word(t_env **env, char **input)
{
	char	*current;
	char	current_quote;

	current = *input;
	while (**input && !is_meta_character(**input) && !ft_isspace(**input))
	{
		if (**input == '\'' || **input == '\"')
		{
			current_quote = **input;
			(*input)++;
			while (**input && **input != current_quote)
			{
				if (current_quote == '\"' && **input == '\\')
					(*input)++;
				(*input)++;
			}
		}
		(*input)++;
	}
	add_token(TOKEN_WORD,
		ft_substr(current, 0, *input - current), ft_isspace(**input), env);
}

void	get_tokens(char *input, t_env **env)
{
	char	*current;

	current = input;
	while (*input)
	{
		while (ft_isspace(*input))
			input++;
		if (is_meta_character(*input))
			handle_meta(env, &input);
		else if (*input == '#' && !is_quote_open(current))
		{
			add_token(TOKEN_EOF, ft_strdup("EOF"), 0, env);
			return ;
		}
		else
			tokenize_word(env, &input);
	}
	add_token(TOKEN_EOF, ft_strdup("EOF"), 0, env);
}

/*
void	handle_illegal(t_env **env, char **input)
{
	char	error[2];

	error[0] = **input;
	error[1] = '\0';
	add_token(TOKEN_ILLEGAL, ft_strdup(error), 0, env);
	(*input)++;
}
*/
