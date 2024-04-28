/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:15:26 by dzuiev            #+#    #+#             */
/*   Updated: 2024/04/28 17:01:54 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// t_ast_node	*new_ast_node(t_token_type type, char **args,
// 				t_ast_node *left, t_ast_node *right)
// {
//     t_ast_node *node;

// 	node = malloc(sizeof(t_ast_node));
// 	if (!node)
// 	{
// 		ft_perror("Memory allocation failed for AST node\n");
// 		return(NULL);
// 	}
// 	node->type = type;
// 	node->args = args;
// 	node->left = left;
// 	node->right = right;
// 	return (node);
// }

// int	get_arg_count(t_token **current)
// {
// 	t_token *temp;
// 	int 	arg_count;

// 	temp = *current;
// 	arg_count = 0;
// 	while (temp && temp->type == TOKEN_WORD)
// 	{
// 		arg_count++;
// 		temp = temp->next;
// 	}
// 	return (arg_count);
// }

// char	**copy_args(t_token **current, t_env **env)
// {
// 	int	arg_count;

// 	arg_count = get_arg_count(current);
// 	char **args = malloc(sizeof(char *) * (arg_count + 1));
// 	if (!args)
// 	{
// 		ft_perror("malloc failed");
// 		cleanup(env, EXIT_FAILURE);
// 	}
// 	args[arg_count] = NULL;
// 	arg_count = 0;
// 	while (*current && (*current)->type == TOKEN_WORD)
// 	{
// 		args[arg_count] = ft_strdup((*current)->value);
// 		if (!args[arg_count])
// 		{
// 			ft_perror("malloc failed");
// 			ft_free_args(&args);
// 			cleanup(env, EXIT_FAILURE);
// 		}
// 		*current = (*current)->next;
// 		arg_count++;
// 	}
// 	return (args);
// }

// t_token *check_ast_input(t_env **env)
// {
// 	t_token *current;

// 	if (!env || !*env)
// 	{
// 		ft_perror("No environment to parse\n");
// 		cleanup(env, EXIT_FAILURE);
// 	}
// 	current = (*env)->tokens;
// 	if (!current || current->type == TOKEN_EOF)
// 	{
// 		ft_perror("No tokens to parse\n");
// 		cleanup(env, EXIT_FAILURE);
// 	}
// 	return (current);
// }

// void check_ast_output(t_token **current, t_env **env)
// {
// 	if ((*env)->ast == NULL)
// 	{
// 		ft_perror("Failed to parse tokens\n");
// 		cleanup(env, EXIT_FAILURE);
// 	}
// 	if ((*current)->type != TOKEN_EOF)
// 	{
// 		ft_perror("Unexpected tokens after parsing\n");
// 		cleanup(env, EXIT_FAILURE);
// 	}
// }

// // Main function to parse the complete command line into an AST
// void	parse_tokens(t_env **env)
// {
// 	t_token		*current;

// 	current = check_ast_input(env);
// 	(*env)->ast = parse_sequence(&current);
// 	check_ast_output(&current, env);
// }
