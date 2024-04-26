/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:15:26 by dzuiev            #+#    #+#             */
/*   Updated: 2024/04/26 14:34:00 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast_node	*new_ast_node(t_token_type type, t_env **env)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
	{
		ft_perror("malloc failed");
		cleanup(env, EXIT_FAILURE);
	}
	node->type = type;
	node->args = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

// t_ast_node *parse_command(t_token **token, t_env **env)
// {
// 	t_ast_node	*node;

// 	if (!*env || !(*env)->tokens
// 		|| !*token || !(*token)->value)
// 		return (NULL);
// 	node = new_ast_node((*token)->type, env);
// 	if (node->type == TOKEN_WORD)
// 	{
// 		int arg_count = 0, arg_capacity = 10;
// 			node->args = malloc(arg_capacity * sizeof(char*));
// 			while (*token && (*token)->type == TOKEN_WORD)
// 			{
// 				if (arg_count >= arg_capacity)
// 				{
// 					arg_capacity *= 2;
// 					node->args = realloc(node->args, arg_capacity * sizeof(char*));
// 				}
// 				node->args[arg_count++] = ft_strdup((*token)->value);
// 				*token = (*token)->next;
// 			}
// 			node->args[arg_count] = NULL;  // Null-terminate the array of arguments
// 		}
// 	else if (node->type == TOKEN_REDIR_INPUT
// 			|| node->type == TOKEN_REDIR_OUTPUT
// 			|| node->type == TOKEN_REDIR_APPEND
// 			|| node->type == TOKEN_HERE_DOC)
// 	{
// 		// Process redirection operators
// 		*token = (*token)->next;  // Move past the redirection operator token
// 		node->left = parse_command(token, env);
// 	}
// 	else if (node->type == TOKEN_PIPE
// 			|| node->type == TOKEN_AND_IF
// 			|| node->type == TOKEN_OR_IF)
// 	{
// 		// Process control operators
// 		*token = (*token)->next;  // Move past the operator token
// 		node->left = parse_command(token, env);
// 		node->right = parse_command(token, env);
// 	}
// 	return (node);
// }

// t_ast_node	*build_ast(t_token *tokens)
// {
// 	t_ast_node	*root;
// 	t_ast_node	*cmd;
// 	t_token		*current;

// 	root = NULL;
// 	current = tokens;
// 	while (current)
// 	{
// 		cmd = parse_command(&current);
// 		if (!root)
// 			root = cmd;
// 		// Можно добавить обработку последовательности команд (не показано)
// 		current = current->next;
// 	}
// 	return root;
// }
