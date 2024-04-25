/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:25:09 by dzuiev            #+#    #+#             */
/*   Updated: 2024/04/24 13:25:09 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	insert_nl_t_v(char **start, char **input, t_dynamic_buffer *buf)
{
	if (*start != *input)
		buffer_append(buf, *start, *input - *start);
	(*input)++;
	if (**input == 'n')
		buffer_append_char(buf, '\n');
	else if (**input == 'v')
		buffer_append_char(buf, '\v');
	else if (**input == 't')
		buffer_append_char(buf, '\t');
	(*input)++;
	*start = *input;
}

// static void	buffer_append_tmp(t_dynamic_buffer *buf, char **start, char **input)
// {
// 	while (**input && **input != '\'' && **input != '\\')
// 		(*input)++;
// 	if (*start != *input)
// 	{
// 		buffer_append(buf, *start, *input - *start);
// 		*start = *input;
// 	}
// }

void	expand_cstyle_string(char **input, char **current, t_dynamic_buffer *buf)
{
	(*input)++;
	*current = *input;
	while (**input && **input != '\'')
	{
		if (**input == '\\' && (*(*input + 1) == 'n'
			|| *(*input + 1) == 'v' || *(*input + 1) == 't'))
			insert_nl_t_v(current, input, buf);
		else
			(*input)++;
	}
	if (*current != *input)
		buffer_append(buf, *current, *input - *current);
	if (**input == '\'')
		(*input)++;
	*current = *input;
}

char	*get_process_id()
{
	pid_t	pid;

	pid = 0;
	pid = getpid();
	return (ft_itoa(pid));
}

void	handle_environment_variable(char **input, char **current, t_dynamic_buffer *buf)
{
	char	*env_name;
	char	*env_value;

	*current = *input;
	if (**input == '$')
	{
		env_value = get_process_id();
		buffer_append(buf, env_value, ft_strlen(env_value));
		free(env_value);
		(*input)++;
	}
	else
	{
		while (**input && (ft_isalnum(**input) || **input == '_'))
			(*input)++;
		env_name = ft_substr(*current, 0, *input - *current);
		env_value = ft_strdup(getenv(env_name));
		buffer_append(buf, env_value, ft_strlen(env_value));
		free(env_name);
		free(env_value);
	}
	if (env_value == NULL)
		buffer_append(buf, "", 0);
	*current = *input;
}

static void	handle_dollar_sign(char **input, char **current, t_dynamic_buffer *buf)
{
	if (*current != *input)
		buffer_append(buf, *current, *input - *current);
	(*input)++;
	if (**input == '\'')
		expand_cstyle_string(input, current, buf);
	else if (ft_isalnum(**input) || **input == '_' || **input == '$')
		handle_environment_variable(input, current, buf);
	*current = *input;
}

void handle_backslach(char **input, char **current, t_dynamic_buffer *buf)
{
	if (*current != *input)
		buffer_append(buf, *current, *input - *current);
	(*input)++;
	if (**input == '\"' || **input == '\\' || **input == '$' || **input == '`')
	{
		buffer_append_char(buf, **input);
		(*input)++;
	}
	*current = *input;
}

void	handle_double_quotes(char **input, char **current, t_dynamic_buffer *buf)
{
	(*input)++;
	*current = *input;
	while (**input && **input != '\"')
	{
		if (**input == '$')
			handle_dollar_sign(input, current, buf);
		if (**input == '\\')
			handle_backslach(input, current, buf);
		if (**input != '$' && **input != '\\')
			(*input)++;
	}
	if (**input == '\"')
	{
		if (*current != *input)
			buffer_append(buf, *current, *input - *current);
		(*input)++;
	}
	*current = *input;
}

static void	handle_single_quotes(char **input, char **current, t_dynamic_buffer *buf)
{
	(*input)++;
	while (**input && **input != '\'')
		(*input)++;
	if (**input == '\'')
	{
		if (*current != *input)
			buffer_append(buf, *current, *input - *current);
		(*input)++;
	}
	*current = *input;
}

void	handle_quotes(char **input, char **current, t_dynamic_buffer *buf)
{
	if (*current != *input)
		buffer_append(buf, *current, *input - *current);
	if (**input == '\"')
		handle_double_quotes(input, current, buf);
	else if (**input == '\'')
		handle_single_quotes(input, current, buf);
	*current = *input;
}

char *expand_word(char **input)
{
	t_dynamic_buffer	buf;
	char				*expanded;
	char				*current;
	char				*start;

	buffer_init(&buf);
	start = *input;
	current = *input;
	while (**input)
	{
		if (**input == '$')
			handle_dollar_sign(input, &current, &buf);
		if (**input == '\'' || **input == '\"')
			handle_quotes(input, &current, &buf);
		if (**input != '$' && **input != '\'' && **input != '\"')
			(*input)++;
	}
	if (current != *input)
		buffer_append(&buf, current, *input - current);
	expanded = strdup(buf.data);
	buffer_free(&buf);
	*input = start;
	return (expanded);
}

void	expand_tokens(t_env **env)
{
	t_token	*token;
	char	*expanded;

	token = (*env)->tokens;
	while (token)
	{
		if (token->type == TOKEN_WORD)
		{
			expanded = expand_word(&token->value);
			free(token->value);
			token->value = expanded;
		}
		token = token->next;
	}
}
