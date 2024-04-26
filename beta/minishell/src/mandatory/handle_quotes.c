/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 08:22:15 by dzuiev            #+#    #+#             */
/*   Updated: 2024/04/26 08:39:26 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_backslach(char **input, char **current,
				t_dynamic_buffer *buf)
{
	if (*current != *input)
		buffer_append(buf, *current, *input - *current);
	(*input)++;
	if (**input == '\"'
		|| **input == '\\'
		|| **input == '$'
		|| **input == '`')
	{
		buffer_append_char(buf, **input);
		(*input)++;
	}
	*current = *input;
}

static void	handle_double_quotes(char **input, char **current,
				t_dynamic_buffer *buf)
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

static void	handle_single_quotes(char **input, char **current,
				t_dynamic_buffer *buf)
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
