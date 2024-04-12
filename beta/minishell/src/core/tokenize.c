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

t_token	*create_token(token_type type, char *value)
{
	t_token *token;
	
	token = malloc(sizeof(t_token));
	if (token == NULL)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	token->type = type;
	token->value = ft_strdup(value); // используем strdup для копирования строки
	token->next = NULL;
	return token;
}

void	add_token(t_token **token_list, t_token *new_token)
{
	t_token *current;
	
	if (*token_list == NULL)
		*token_list = new_token;
	else
	{
		current = *token_list;
		while (current->next != NULL)
			current = current->next;
		current->next = new_token;
	}
}

void	free_tokens(t_token *tokens)
{
	t_token *current;
	while (tokens != NULL)
	{
		current = tokens;
		tokens = tokens->next;
		free(current->value);
		free(current);
	}
}

int	is_special_character(char c)
{
	return (c == '<' || c == '>' || c == '|' || c == '&' || c == ';');
}

void	handle_special(t_token **tokens, char **input)
{
	char *start;
	char special[3];
	
	start = *input;
	*special = {0};
	special[0] = *start;
	if (*start == '<')
	{
		if (*(start + 1) == '<')
		{
			special[1] = '<';
			(*input)++;
			add_token(tokens, create_token(TOKEN_HERE_DOC, special));
		}
		else
			add_token(tokens, create_token(TOKEN_REDIR_INPUT, special));
	}
	else if (*start == '>')
	{
		if (*(start + 1) == '>')
		{
			special[1] = '>';
			(*input)++;
			add_token(tokens, create_token(TOKEN_REDIR_APPEND, special));
		}
		else
			add_token(tokens, create_token(TOKEN_REDIR_OUTPUT, special));
	}
	else if (*start == '|')
	{
		if (*(start + 1) == '|')
		{
			special[1] = '|';
			(*input)++;
			add_token(tokens, create_token(TOKEN_OR, special));
		}
		else
			add_token(tokens, create_token(TOKEN_PIPE, special));
	}
	else if (*start == '&')
	{
		if (*(start + 1) == '&')
		{
			special[1] = '&';
			(*input)++;
			add_token(tokens, create_token(TOKEN_AND, special));
		}
	}
	else if (*start == ';')
		add_token(tokens, create_token(TOKEN_SEMI, special));
	(*input)++;
}

void	handle_word(t_token **tokens, char **input)
{
	char *start = *input;
	while (**input && !isspace(**input) && !is_special_character(**input))
	{
		(*input)++;
	}
	int length = *input - start;
	char *word = malloc(length + 1);
	if (word == NULL)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	strncpy(word, start, length);
	word[length] = '\0';
	add_token(tokens, create_token(TOKEN_WORD, word));
	free(word);
}

void handle_illegal(t_token **tokens, char **input)
{
	char error[2] = {*input, '\0'};
	add_token(tokens, create_token(TOKEN_ILLEGAL, error));
	(*input)++;
}

void check_and_add_token(t_token **tokens, char *start, int length, token_type type)
{
	if (length > 0) 
	{
		char *value = malloc(length + 1);
		if (!value)
		{
			perror("malloc failed");
			exit(EXIT_FAILURE);
		}
		strncpy(value, start, length);
		value[length] = '\0';
		add_token(tokens, create_token(type, value));
		free(value);
	}
	else
		handle_illegal(tokens, &start);
}

void	tokenize_string(t_token **tokens, char **input)
{
	char *start = *input;
	(*input)++;  // Skip the opening quote
	while (**input && **input != *start)
	{
		if (**input == '\\') (*input)++;  // Skip the escape character
		if (**input) (*input)++;
	}
	if (**input == *start)
	{
		check_and_add_token(tokens, start + 1, *input - start - 1, TOKEN_WORD);
		(*input)++;  // Skip the closing quote
	}
	else
		handle_illegal(tokens, input);
}

void tokenize(char *input)
{
	t_token *tokens = NULL;
	char *original_input = input;

	while (*input)
	{
		if (isspace(*input))
			input++;  // Skip whitespace
		else if (is_special_character(*input))
			handle_special(&tokens, &input);
		else if (*input == '\'' || *input == '"')
			tokenize_string(&tokens, &input);
		else if (isalpha(*input) || isdigit(*input) || *input == '_')
			handle_word(&tokens, &input);
		else
			handle_illegal(&tokens, &input);
	}
	if (input == original_input || *input == '\0')
		add_token(&tokens, create_token(TOKEN_EOF, "EOF"));
	// Вывод токенов для дебага (можно удалить в финальной версии)
	t_token *temp = tokens;
	while (temp != NULL)
	{
		printf("Type: %d, Value: %s\n", temp->type, temp->value);
		temp = temp->next;
	}
	free_tokens(tokens);
}

int main() {
    // Назначение обработчика сигнала

    char *input;
    while (1) {
        input = readline("minishell> ");
        if (input == NULL) {
            // Обработка EOF, если пользователь ввел ctrl-D
            printf("\n");
            break;
        }
        // Добавьте обработку ввода здесь
		if (input)
        	free(input);
    }

    return 0;
}
