/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:29:58 by dzuiev            #+#    #+#             */
/*   Updated: 2024/04/12 17:52:59 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_token
{
	token_type	type;
	char	*value;
	struct s_token	*next;
}				t_token;

typedef enum
{
	TOKEN_WORD, // word = any sequence of characters that is not a special character
	TOKEN_REDIR_INPUT, // <
	TOKEN_REDIR_OUTPUT, // >
	TOKEN_REDIR_APPEND, // >>
	TOKEN_HERE_DOC, // <<
	TOKEN_PIPE, // |
	TOKEN_AND, // &
	TOKEN_OR, // ||
	TOKEN_SEMI, // ;
	TOKEN_ILLEGAL, // illegal token - for error handling
	TOKEN_EOF // end of file - for lexer termination condition
}				token_type;

// Вспомогательные функции
t_token	*create_token(token_type type, char *value);
void	add_token(t_token **token_list, t_token *new_token);
void	free_tokens(t_token *tokens);

#endif
