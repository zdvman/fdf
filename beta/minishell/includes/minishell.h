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
# include <stdbool.h>
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
/*        TOKEN_PIPE,            |                                            */
/*		  TOKEN_BACKGROUND,      &                                            */
/*        TOKEN_AND_IF,          &&                                           */
/*        TOKEN_OR_IF,           ||                                           */
/*        TOKEN_SEMI,            ;                                            */
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
	TOKEN_AND_IF,
	TOKEN_OR_IF,
	TOKEN_SEMI,
	TOKEN_BACKGROUND,
	TOKEN_OPEN_BRACKET,
	TOKEN_CLOSE_BRACKET,
	TOKEN_EOF
}				t_token_type;

typedef struct s_ast_node
{
	t_token_type 		type;          // Тип узла (команда, пайплайн, логический оператор)
	char				**args;        // Аргументы команды
	struct s_ast_node	*left;         // Левый ребенок в дереве (для операторов)
	struct s_ast_node	*right;        // Правый ребенок в дереве (для операторов)
}				t_ast_node;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	int				has_space;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

typedef struct s_env
{
	char			**envp;
	int				exit_status;
	t_ast_node		*ast;
	t_token			*tokens;
	t_token			*head_token;
}				t_env;

typedef struct s_dynamic_buffer
{
	char	*data;
	size_t	len;
	size_t	capacity;
}				t_dynamic_buffer;

// init.c
void	shell_init(t_env **env, char **envp);

// dynamic_buffer.c
void	buffer_init(t_dynamic_buffer *buf);
void	buffer_free(t_dynamic_buffer *buf);
void	buffer_clear(t_dynamic_buffer *buf);
int		buffer_append_char(t_dynamic_buffer *buf, char c);
int		buffer_append(t_dynamic_buffer *buf, const char *str, size_t n);

// free_utils.c
void	cleanup(t_env **env, int status);
void	ft_free_args(char ***args);

// utils.c
void	set_sig_actions(void);

// expand.c
void	expand_tokens(t_env **env);
char	*expand_word(char **input);

// multiline_and_quotes_input.c
char	*read_multiline(void);
int		is_quote_open(const char *input);

// handle_meta_redirs_pipe_or.c
void	handle_greater_than_sign(t_env **env, char **input);
void	handle_less_than_sign(t_env **env, char **input);
void	handle_pipe_or(t_env **env, char **input);
void	handle_and(t_env **env, char **input);

// handle_meta_brackets_semi.c
void	handle_semicolon(t_env **env, char **input);
void	handle_open_bracket(t_env **env, char **input);
void	handle_close_bracket(t_env **env, char **input);

// handle_quotes.c
void	handle_quotes(char **input, char **current, t_dynamic_buffer *buf);

// handle_dollar.c
void	handle_dollar_sign(char **input, char **current, t_dynamic_buffer *buf);

// get_tokens.c
void	add_token(t_token_type type, char *value, int space_after, t_env **env);
int		is_meta_character(char c);
void	handle_meta(t_env **env, char **input);
void	get_tokens(char *input, t_env **env);

#endif
