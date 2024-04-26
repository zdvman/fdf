/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:39:53 by dzuiev            #+#    #+#             */
/*   Updated: 2024/04/26 09:19:49 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                 Minishell                                  */
/*  Project structure:                                                        */
/*   minishell/                                                               */
/*  ├── libft/                   Libft library files                          */
/*  │   ├── obj/                 Libft object files                           */
/*  │   ├── Makefile             Makefile to build the libft library          */
/*  │   └── ...                  Libft source files and headers               */
/*  ├── src/                     Source files for Minishell core functionality*/
/*  │   ├── mandatory/           Source files from mandatory sources          */
/*  │   ├── bonus/               Source files from bonus sources              */
/*  │   └── main.c               Main file for the Minishell project          */
/*  ├── includes/                Header files for all Minishell parts         */
/*  │   ├── minishell.h          Main headers for the project                 */
/*  │   └── minishell_bonus.h    Bonus headers for the project                */
/*  ├── obj/                     Object files for all Minishell parts         */
/*  │   ├── mandatory/           Object files from mandatory sources          */
/*  │   ├── bonus/               Object files from bonus sources              */
/*  ├── Makefile                 Makefile to build the minishell project      */
/*  └── README.md                Documentation of the project                 */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#ifdef BONUS
# include "../includes/minishell_bonus.h"
#endif

void	print_token_name(t_token *token)
{
	if (token->type == TOKEN_WORD)
		printf("TOKEN_WORD         :");
	else if (token->type == TOKEN_BACKGROUND)
		printf("TOKEN_BACKGROUND   :");
	else if (token->type == TOKEN_REDIR_INPUT)
		printf("TOKEN_REDIR_INPUT  :");
	else if (token->type == TOKEN_REDIR_OUTPUT)
		printf("TOKEN_REDIR_OUTPUT :");
	else if (token->type == TOKEN_REDIR_APPEND)
		printf("TOKEN_REDIR_APPEND :");
	else if (token->type == TOKEN_HERE_DOC)
		printf("TOKEN_HERE_DOC     :");
	else if (token->type == TOKEN_PIPE)
		printf("TOKEN_PIPE         :");
	else if (token->type == TOKEN_AND_IF)
		printf("TOKEN_AND_IF       :");
	else if (token->type == TOKEN_OR_IF)
		printf("TOKEN_OR_IF        :");
	else if (token->type == TOKEN_SEMI)
		printf("TOKEN_SEMI         :");
	else if (token->type == TOKEN_OPEN_BRACKET)
		printf("TOKEN_OPEN BRACKET :");
	else if (token->type == TOKEN_CLOSE_BRACKET)
		printf("TOKEN_CLOSE BRACKET:");
	else if (token->type == TOKEN_EOF)
		printf("TOKEN_EOF          :");
}

int	main(int argc, char **argv, char **envp)
{
	t_token	*current;
	t_env	*env;
	char	*input;

	if (argc != 1)
	{
		printf("Usage: ./%s\n", argv[0]);
		return (EXIT_FAILURE);
	}
	shell_init(&env, envp);
	input = NULL;
	while (1)
	{
		input = read_multiline();
		if (input == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (input && *input)
		{
			add_history(input);
			get_tokens(input, &env);
			expand_tokens(&env);
		}
		if (input)
			free(input);
	}
	current = env->tokens;
	while (current)
	{
		print_token_name(current);
		printf(" space: %s", current->has_space ? "true ;" : "false;");
		printf(" %s\n", current->value);
		current = current->next;
	}
	cleanup(&env, 0);
	return (0);
}
