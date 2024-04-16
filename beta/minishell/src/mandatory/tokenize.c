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

// #include "../../includes/minishell.h"


// void	handle_word(t_token **tokens, char **input)
// {
// 	char *start = *input;
// 	while (**input && !isspace(**input) && !is_special_character(**input))
// 	{
// 		(*input)++;
// 	}
// 	int length = *input - start;
// 	char *word = malloc(length + 1);
// 	if (word == NULL)
// 	{
// 		perror("malloc failed");
// 		exit(EXIT_FAILURE);
// 	}
// 	strncpy(word, start, length);
// 	word[length] = '\0';
// 	add_token(tokens, create_token(TOKEN_WORD, word));
// 	free(word);
// }

// void handle_illegal(t_token **tokens, char **input)
// {
// 	char error[2] = {*input, '\0'};
// 	add_token(tokens, create_token(TOKEN_ILLEGAL, error));
// 	(*input)++;
// }

// void check_and_add_token(t_token **tokens, char *start, int length, token_type type)
// {
// 	if (length > 0) 
// 	{
// 		char *value = malloc(length + 1);
// 		if (!value)
// 		{
// 			perror("malloc failed");
// 			exit(EXIT_FAILURE);
// 		}
// 		strncpy(value, start, length);
// 		value[length] = '\0';
// 		add_token(tokens, create_token(type, value));
// 		free(value);
// 	}
// 	else
// 		handle_illegal(tokens, &start);
// }

// void	tokenize_string(t_token **tokens, char **input)
// {
// 	char *start = *input;
// 	(*input)++;  // Skip the opening quote
// 	while (**input && **input != *start)
// 	{
// 		if (**input == '\\') (*input)++;  // Skip the escape character
// 		if (**input) (*input)++;
// 	}
// 	if (**input == *start)
// 	{
// 		check_and_add_token(tokens, start + 1, *input - start - 1, TOKEN_WORD);
// 		(*input)++;  // Skip the closing quote
// 	}
// 	else
// 		handle_illegal(tokens, input);
// }


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

// int is_not_in_quotes(t_token **tokens)
// {
// 	int in_quotes;
// 	in_quotes = 0;
// 	while (tokens && tokens->type != TOKEN_EOF)
// 	{
// 		if (tokens->type == TOKEN_WORD && (ft_strchr(tokens->value, '\'') || ft_strchr(tokens->value, '"')))
// 			in_quotes = !in_quotes;
// 		tokens = tokens->next;
// 	}
// 	return (in_quotes);
// }

void tokenize_string(t_token **tokens, char **input)
{
	char *start = *input;
	char current_quote = **input;

	(*input)++;  // Пропускаем начальную кавычку
	while (**input && **input != current_quote) {
		// if (current_quote == '\"' && **input == '\\') {
		// 	if (*(*input + 1) == '\"' || *(*input + 1) == '\\')
		// 	{
		// 		// Пропускаем символ экранирования только для специфических символов
		// 		(*input)++;
		// 	}
		// } else if (current_quote == '\"' && **input == '$') {
		// 	// Здесь должна быть реализация обработки переменных окружения
		// 	// Эта функция должна возвращать обработанную строку, которую надо добавить к текущему значению токена
		// 	char *env_value = handle_environment_variable(input); // Реализуйте эту функцию в соответствии с вашими требованиями
		// 	append_to_token_value(env_value, tokens);  // Добавляйте значение переменной к текущему токену
		// 	free(env_value);  // Не забудьте освободить память
		// 	continue;
		// }
		(*input)++;
	}

	if (**input == current_quote) {  // Проверяем, закрыта ли кавычка
		add_token(TOKEN_WORD, ft_substr(start + 1, 0, *input - start - 1), tokens);
		(*input)++;
	// } else {
	// 	handle_illegal(tokens, input);  // Обработка случая, когда кавычка не закрыта
	}
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
	// else if (*start == '$')
	// 	add_token(TOKEN_DOLLAR, "$", tokens);
	// else if (*start == '#')
	// 	handle_hash(tokens, &start, is_not_in_quotes(*tokens)

		
	// else if (*start == '#' && is_not_in_quotes(*start))
	// 	handle_comment(tokens, &start);
	// else
	// 	handle_illegal(tokens, &start);
		
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
		// else if (isalpha(*input) || isdigit(*input) || *input == '_')
		// 	handle_word(tokens, &input);
		// else
		// 	handle_illegal(tokens, &input);
		// input++;
	}
	if (input == start || *input == '\0')
		add_token(TOKEN_EOF, ft_strdup("EOF"), tokens);
}
