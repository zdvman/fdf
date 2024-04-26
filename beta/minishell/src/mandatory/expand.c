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

char	*expand_word(char **input)
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
