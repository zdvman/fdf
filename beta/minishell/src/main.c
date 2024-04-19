/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:39:53 by dzuiev            #+#    #+#             */
/*   Updated: 2024/04/19 18:41:52 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/******************************************************************************/
/*                                Minishell                                   */
/* Project structure:                                                         */
/*  minishell/                                                                */
/* ├── libft/              # Libft library files                              */
/* │   ├── Makefile                                                           */
/* │   └── ...             # Libft source files and headers                   */
/* ├── src/                # Source files for Minishell                       */
/* │   ├── core/           # Core functionality for both parts                */
/* │   │   └── ...         # Core implementation files                        */
/* │   ├── mandatory/      # Mandatory specific files                         */
/* │   │   └── ...         # Mandatory implementation files                   */
/* │   ├── bonus/          # Bonus specific files (if any)                    */
/* │   │   └── ...         # Bonus implementation files                       */
/* │   └── main.c          # Main program entry point                         */
/* ├── includes/           # Header files                                     */
/* │   ├── minishell.h                                                        */
/* │   └── bonus_features.h                                                   */
/* ├── Makefile                                                               */
/* └── README.md                                                              */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"
#ifdef BONUS
# include "../includes/minishell_bonus.h"
#endif

void	print_token_name(t_token *token)
{
	if (token->type == TOKEN_WORD)
		printf("TOKEN_WORD         :");
	else if (token->type == TOKEN_STRING)
		printf("TOKEN_STRING       :");
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
	else if (token->type == TOKEN_AND)
		printf("TOKEN_AND          :");
	else if (token->type == TOKEN_OR)
		printf("TOKEN_OR           :");
	else if (token->type == TOKEN_SEMI)
		printf("TOKEN_SEMI         :");
	// else if (token->type == TOKEN_SINGLE_QUOTE)
	// 	printf("TOKEN_SINGLE_QUOTE :");
	// else if (token->type == TOKEN_DOUBLE_QUOTE)
	// 	printf("TOKEN_DOUBLE_QUOTE :");
	else if (token->type == TOKEN_ENV_VAR)
		printf("TOKEN_ENV_VAR      :");
	else if (token->type == TOKEN_EQUAL)
		printf("TOKEN_EQUAL        :");
	else if (token->type == TOKEN_ILLEGAL)
		printf("TOKEN_ILLEGAL 	   :");
}

void	tokens_init(t_token **tokens)
{
	(*tokens)->value = NULL;
	(*tokens)->next = NULL;
	(*tokens)->prev = NULL;
}


void shell_init(t_env **env, t_token **tokens, char **envp)
{
	int	i;
	int	env_len;

	i = 0;
	env_len = ft_strarr_len(envp);
	*tokens = malloc(sizeof(t_token));
	*env = malloc(sizeof(t_env));
	(*env)->envp = malloc(sizeof(char *) * (env_len + 1));
	if (tokens == NULL || *env == NULL || (*env)->envp == NULL)
	{
		ft_perror("malloc failed\n");
		cleanup(env, EXIT_FAILURE);
	}
	(*env)->envp[env_len] = NULL;
	while (envp[i] != NULL)
	{
		(*env)->envp[i] = ft_strdup(envp[i]);
		if ((*env)->envp[i] == NULL)
		{
			ft_perror("malloc failed\n");
			cleanup(env, EXIT_FAILURE);
		}
		printf("%s\n", (*env)->envp[i]);
		i++;
	}
	tokens_init(tokens);
	(*env)->token = *tokens;
	(*env)->head_token = *tokens;
	printf("\033[?12h");
	set_sig_actions();
}

int	main(int argc, char **argv, char **envp)
{
	t_token	*tokens;
	t_token	*current;
	t_env	*env;
	char	*input;

	if (argc != 1)
	{
		printf("Usage: ./%s\n", argv[0]);
		return (EXIT_FAILURE);
	}
	shell_init(&env, &tokens, envp);
	// printf("\033[?12h");
	// set_sig_actions();
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
			tokenize(input, &tokens);
		}
		if (input)
			free(input);
	}
	current = tokens;
	while (current)
	{
		print_token_name(current);
		printf(" %s\n", current->value);
		current = current->next;
	}
	cleanup(&env, 0);
	return (0);
}
