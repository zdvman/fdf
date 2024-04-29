/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:39:53 by dzuiev            #+#    #+#             */
/*   Updated: 2024/04/29 13:49:32 by dzuiev           ###   ########.fr       */
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

void print_escaped(FILE *stream, const char *str)
{
	if (!str) return;
	while (*str)
	{
		switch (*str)
		{
			case '\n': fprintf(stream, "\\n"); break;
			case '\"': fprintf(stream, "\\\""); break;
			case '\\': fprintf(stream, "\\\\"); break;
			default: fputc(*str, stream);
		}
		str++;
	}
}

void print_ast_dot(t_ast_node *node, FILE *stream)
{
	if (node == NULL) return;

	fprintf(stream, "\"%p\" [label=\"", (void*)node);
	// Print node type
	switch (node->type)
	{
		// Adjust these labels based on your specific types and what they represent
		case TOKEN_WORD: fprintf(stream, "CMD: "); break;
		case TOKEN_REDIR_INPUT:
		case TOKEN_REDIR_OUTPUT:
		case TOKEN_REDIR_APPEND:
		case TOKEN_HERE_DOC: fprintf(stream, "REDIR: "); break;
		case TOKEN_PIPE: fprintf(stream, "|"); break;
		case TOKEN_BACKGROUND: fprintf(stream, "&"); break;
		case TOKEN_AND_IF: fprintf(stream, "&&"); break;
		case TOKEN_OR_IF: fprintf(stream, "||"); break;
		case TOKEN_SEMI: fprintf(stream, ";"); break;
		break;
		default: fprintf(stream, "UNKNOWN"); break;
	}
	// Print all arguments for the node
	if (node->args)
	{
		for (int i = 0; node->args[i] != NULL; i++)
		{
			if (i > 0) fprintf(stream, " "); // Add space between arguments
			print_escaped(stream, node->args[i]);
		}
	}
	fprintf(stream, "\"];\n");
	if (node->left != NULL)
	{
		fprintf(stream, "\"%p\" -> \"%p\" [label=\"L\"];\n", (void*)node, (void*)node->left);
		print_ast_dot(node->left, stream);
	}
	if (node->right != NULL)
	{
		fprintf(stream, "\"%p\" -> \"%p\" [label=\"R\"];\n", (void*)node, (void*)node->right);
		print_ast_dot(node->right, stream);
	}
}

void	generate_ast_diagram(t_ast_node *root)
{
	FILE *stream = fopen("ast.dot", "w");
	if (stream == NULL)
	{
		perror("fopen");
		return;
	}

	fprintf(stream, "digraph AST {\n");
	print_ast_dot(root, stream);
	fprintf(stream, "}\n");
	fclose(stream);
}

int	main(int argc, char **argv, char **envp)
{
	t_token	*current;
	t_env	*env;
	t_ast_node	*ast;
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
			write(1, "exit\n", 5);
			break ;
		}
		if (input && *input)
		{
			add_history(input);
			get_tokens(input, &env);
			expand_tokens(&env);
			parse_tokens(&env);
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
	ast = env->ast;
	if (ast)
	{
		generate_ast_diagram(ast);
	}
	cleanup(&env, 0);
	return (0);
}
