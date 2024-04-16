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
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

/* ************************************************************************** */
/*                                                                            */
/*  typedef enum e_token_type {                                               */
/*        TOKEN_WORD,            word                                         */
/*        TOKEN_REDIR_INPUT,     <                                            */
/*        TOKEN_REDIR_OUTPUT,    >                                            */
/*        TOKEN_REDIR_APPEND,    >>                                           */
/*        TOKEN_HERE_DOC,        <<                                           */
/*        TOKEN_OPEN_BRACKET,    (                                            */
/*        TOKEN_CLOSE_BRACKET,   )                                            */
/*        TOKEN_AND,             &                                            */
/*        TOKEN_OR,              ||                                           */
/*        TOKEN_SEMI,            ;                                            */
/*        TOKEN_ILLEGAL,         illegal token - for error handling           */
/*        TOKEN_EOF              end of file - for lexer termination condition*/
/*    } token_type;                                                           */
/*                                                                            */
/* ************************************************************************** */

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_REDIR_INPUT,
	TOKEN_REDIR_OUTPUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HERE_DOC,
	TOKEN_PIPE,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_SEMI,
	TOKEN_SINGLE_QUOTE,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_DOLLAR,
	TOKEN_ENV_VAR,
	TOKEN_COMMAND_SUBSTITUTION,
	TOKEN_OPEN_BRACKET,
	TOKEN_CLOSE_BRACKET,
	TOKEN_ILLEGAL,
	TOKEN_EOF
}				t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}				t_token;

// utils.c
void	cleanup(t_token **tokens, int exit_code);
void	handle_sigint(int sig);
void	set_sig_actions(void);

// handle_special.c
int		is_special_character(char c);
void	handle_greater_than_sign(t_token **tokens, char **input);
void	handle_less_than_sign(t_token **tokens, char **input);
void	handle_pipe_or(t_token **tokens, char **input);
void	handle_and(t_token **tokens, char **input);
void	handle_semicolon(t_token **tokens, char **input);
void	handle_open_bracket(t_token **tokens, char **input);
void	handle_close_bracket(t_token **tokens, char **input);


// tokenize.c
void	add_token(t_token_type type, char *value, t_token **tokens);
void	handle_special(t_token **tokens, char **input);
void	tokenize(char *input, t_token **tokens);

#endif
