/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 08:31:35 by dzuiev            #+#    #+#             */
/*   Updated: 2024/04/30 23:47:37 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_redirection(t_token_type type)
{
	if (type == TOKEN_REDIR_INPUT
		|| type == TOKEN_REDIR_OUTPUT
		|| type == TOKEN_REDIR_APPEND
		|| type == TOKEN_HERE_DOC)
			return true;
	else
		return (false);
}

t_ast_node *parse_command(t_token **current, t_env **env)
{
	t_ast_node		*cmd_node;
	t_token_type	type;
	char			**args;

	args = copy_args(current, env);
	cmd_node = new_ast_node(TOKEN_WORD, args, NULL, NULL);
	while (*current && (is_redirection((*current)->type) || (*current)->type == TOKEN_BACKGROUND))
	{
		type = (*current)->type;
		*current = (*current)->next;
		if (type == TOKEN_BACKGROUND)
			cmd_node = new_ast_node(type, NULL, cmd_node, NULL);
		if (!*current || (*current)->type != TOKEN_WORD)
		{
			ft_perror("Expected filename for redirection\n");
			return (NULL);
		}
		args = copy_args(current, env);
		cmd_node = new_ast_node(type, args, cmd_node, NULL);
	}
	return (cmd_node);
}

t_ast_node	*parse_pipeline(t_token **current, t_env **env)
{
	t_ast_node		*left;
	t_ast_node		*right;
	t_token_type	type;

	left = parse_command(current, env);
	while (*current && (*current)->type == TOKEN_PIPE)
	{
		type = (*current)->type;
		*current = (*current)->next;
		right = parse_command(current, env);
		left = new_ast_node(type, NULL, left, right);
	}
	return (left);
}

t_ast_node	*parse_bracket(t_token **current, t_env **env)
{
	t_ast_node		*node;

	if (!*current || (*current)->type != TOKEN_OPEN_BRACKET)
	{
		ft_perror("Expected open bracket\n");
		return (NULL);
	}
	*current = (*current)->next;
	node = parse_sequence(current, env);
	if (!*current || (*current)->type != TOKEN_CLOSE_BRACKET)
	{
		ft_perror("Expected close bracket\n");
		return (NULL);
	}
	*current = (*current)->next;
	return (node);
}

t_ast_node	*parse_sequence(t_token **current, t_env **env)
{
	t_ast_node		*left;
	t_ast_node		*right;
	t_token_type	type;

	if (*current && (*current)->type == TOKEN_OPEN_BRACKET)
	{
		left = parse_bracket(current, env);
	}
	else
	{
		left = parse_pipeline(current, env);
	}
	while (*current && ((*current)->type == TOKEN_SEMI
						|| (*current)->type == TOKEN_AND_IF
						|| (*current)->type == TOKEN_OR_IF))
	{
		type = (*current)->type;
		*current = (*current)->next;
		if (*current && (*current)->type == TOKEN_OPEN_BRACKET)
		{
			right = parse_bracket(current, env);
		}
		else
		{
			right = parse_pipeline(current, env);
		}
		left = new_ast_node(type, NULL, left, right);
	}
	return (left);
}
