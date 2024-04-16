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

void	add_token(t_token_type type, char *value, t_token **tokens)
{
	t_token *token;
	t_token *current;

	current = *tokens;
	token = malloc(sizeof(t_token));
	if (token == NULL)
	{
		ft_perror("malloc failed\n");
		cleanup(tokens, EXIT_FAILURE);
	}
	token->type = type;
	token->value = value;
	token->next = NULL;
	if (*tokens == NULL)
		*tokens = token;
	else
	{
		current = *tokens;
		while (current->next != NULL)
			current = current->next;
		current->next = token;
	}
}

void handle_illegal(t_token **tokens, char **input)
{
	char error[2] = {**input, '\0'};
	add_token(TOKEN_ILLEGAL, ft_strdup(error), tokens);
	(*input)++;
}

char *handle_environment_variable(char **input)
{
	char *start;
	
	start = *input + 1; // Пропустим начальный символ '$'
	(*input)++; // Пропустим символ '$'
	while (**input && (ft_isalnum(**input) || **input == '_'))
		(*input)++;
	char *env_name = ft_substr(start, 0, *input - start);
	char *env_value = getenv(env_name);
	free(env_name); // Освободим имя после использования
	if (env_value == NULL)
		return ft_strdup(""); // Возвращаем пустую строку, если переменная не найдена
	return (ft_strdup(env_value)); // Возвращаем копию строки значения переменной
}


void tokenize_string(t_token **tokens, char **input)
{
	t_dynamic_buffer	buffer;
	char				*start;
	char				current_quote;
	char				*env_value;

	buffer_init(&buffer);
	current_quote = **input;
	start = *input + 1;
	(*input)++;  // Пропускаем начальную кавычку
	while (**input && **input != current_quote) {
		if (current_quote == '\"' && **input == '\\')
		{
			if (*(*input + 1) == '\"' || *(*input + 1) == '\\')
				(*input)++;
		}
		else if (current_quote == '\"' && **input == '$')
		{
			buffer_append(&buffer, start, *input - start);  // Add text before $
			env_value = handle_environment_variable(input);
			buffer_append(&buffer, env_value, ft_strlen(env_value));  // Add env value
			free(env_value);
			start = *input;
			continue;
		}
		else
			(*input)++;
	}
	if (**input == current_quote)
	{ 
		buffer_append(&buffer, start, *input - start);
		add_token(TOKEN_WORD, ft_strdup(buffer.data), tokens);
		(*input)++;
	}
	else
		handle_illegal(tokens, input);  // Обработка случая, когда кавычка не закрыта
	buffer_free(&buffer);
}


void handle_special(t_token **tokens, char **input)
{
	char *start;

	start = *input;
	if (*start == '<')
		handle_less_than_sign(tokens, &start);
	else if (*start == '>')
		handle_greater_than_sign(tokens, &start);
	else if (*start == '|')
		handle_pipe_or(tokens, &start);
	else if (*start == '&')
		handle_and(tokens, &start);
	else if (*start == ';')
		handle_semicolon(tokens, &start);
	else if (*start == '(')
		handle_open_bracket(tokens, &start);
	else if (*start == ')')
		handle_close_bracket(tokens, &start);
	*input = start;
}

void	tokenize(char *input, t_token **tokens)
{
	char *start;
	
	start = input;
	while (*input)
	{
		if (ft_isspace(*input))
			input++;
		else if (is_special_character(*input))
			handle_special(tokens, &input);
		else if (*input == '\'' || *input == '\"')
			tokenize_string(tokens, &input);
	}
	if (input == start || *input == '\0')
		add_token(TOKEN_EOF, ft_strdup("EOF"), tokens);
}
