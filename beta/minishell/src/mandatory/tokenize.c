/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:15:03 by dzuiev            #+#    #+#             */
/*   Updated: 2024/04/12 14:38:55 by dzuiev           ###   ########.fr       */
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

void	handle_illegal(t_env **env, char **input)
{
	char	error[2];

	error[0] = **input;
	error[1] = '\0';
	add_token(TOKEN_ILLEGAL, ft_strdup(error), 0, env);
	(*input)++;
}

void	handle_meta(t_env **env, char **input)
{
	char	*start;

	start = *input;
	if (*start == '<')
		handle_less_than_sign(env, &start);
	else if (*start == '>')
		handle_greater_than_sign(env, &start);
	else if (*start == '|')
		handle_pipe_or(env, &start);
	else if (*start == '&')
		handle_and(env, &start);
	else if (*start == ';')
		handle_semicolon(env, &start);
	else if (*start == '(')
		handle_open_bracket(env, &start);
	else if (*start == ')')
		handle_close_bracket(env, &start);
	*input = start;
}

void	tokenize_env_name_to_val(t_env **env, char **input)
{
	char	*start;
	char	*env_value;
	char	*env_name;

	start = *input + 1;
	(*input)++;
	while (**input && (ft_isalnum(**input) || **input == '_'))
		(*input)++;
	env_name = ft_substr(start, 0, *input - start);
	env_value = getenv(env_name);
	free(env_name);
	if (env_value == NULL)
		env_value = ft_strdup("");
	add_token(TOKEN_ENV_VAR, ft_strdup(env_value), ft_isspace(*(*input)), env);
}

void	tokenize_word(t_env **env, char **input)
{
	char	*start;
	char	current_quote;

	start = *input;
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
	add_token(TOKEN_WORD, ft_substr(start, 0, *input - start), ft_isspace(**input), env);
}

void	get_tokens(char *input, t_env **env)
{
	char	*start;

	start = input;
	while (*input)
	{
		while (ft_isspace(*input))
			input++;
		if (is_meta_character(*input))
			handle_meta(env, &input);
		else if (*input == '#' && !is_quote_open(start))
		{
			add_token(TOKEN_EOF, ft_strdup("EOF"), 0, env);
			return ;
		}
		else
			tokenize_word(env, &input);
	}
	if (input == start || *input == '\0')
		add_token(TOKEN_EOF, ft_strdup("EOF"), 0, env);
}
