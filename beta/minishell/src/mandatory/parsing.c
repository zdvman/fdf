/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 08:31:35 by dzuiev            #+#    #+#             */
/*   Updated: 2024/04/29 16:27:50 by dzuiev           ###   ########.fr       */
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

t_ast_node *parse_command(t_token **token, t_env **env)
{
	char			**args;
	char			**redir_args;
	t_token_type	redir_type;
	t_ast_node		*cmd_node;

	if ((*token)->type != TOKEN_WORD)
	{
		ft_perror("Expected a command word\n");
		return (NULL);
	}
	args = copy_args(token, env);
	cmd_node = new_ast_node(TOKEN_WORD, args, NULL, NULL);
	while (*token && ((*token)->type == TOKEN_REDIR_INPUT
					|| (*token)->type == TOKEN_REDIR_OUTPUT
					|| (*token)->type == TOKEN_REDIR_APPEND
					|| (*token)->type == TOKEN_HERE_DOC))
	{
		redir_type = (*token)->type;
		*token = (*token)->next;
		if (!*token || (*token)->type != TOKEN_WORD)
		{
			ft_perror("Expected filename for redirection\n");
			cleanup(env, EXIT_FAILURE);
		}
		redir_args = copy_args(token, env);
		cmd_node = new_ast_node(redir_type, redir_args, cmd_node, NULL);
	}
	return (cmd_node);
}

t_ast_node	*apply_redirection(t_token **token, t_env **env, t_ast_node *subtree)
{
    t_token_type	redir_type;
    char			**redir_args;

	redir_type = (*token)->type;
    *token = (*token)->next;
    if (!*token || (*token)->type != TOKEN_WORD)
	{
        ft_perror("Expected filename for redirection\n");
        cleanup(env, EXIT_FAILURE);
    }
	redir_args = copy_args(token, env);
	*token = (*token)->next;
    return (new_ast_node(redir_type, redir_args, subtree, NULL));
}

t_ast_node	*parse_pipeline(t_token **token, t_env **env)
{
	t_ast_node	*pipeline;
	t_ast_node	*command;

	pipeline = parse_command(token, env);
	while (*token && (*token)->type == TOKEN_PIPE)
	{
		*token = (*token)->next;
		command = parse_command(token, env);
		pipeline = new_ast_node(TOKEN_PIPE, NULL, pipeline, command);
	}
	if (*token && is_redirection((*token)->type))
			pipeline = apply_redirection(token, env, pipeline);
	return (pipeline);
}

t_ast_node	*parse_logical(t_token **token, t_env **env)
{
	t_ast_node		*left;
	t_ast_node		*right;
	t_token_type	type;

	left = parse_pipeline(token, env);
	while (*token && ((*token)->type == TOKEN_AND_IF
					|| (*token)->type == TOKEN_OR_IF))
	{
		type = (*token)->type;
		*token = (*token)->next;
		right = parse_pipeline(token, env);
		left = new_ast_node(type, NULL, left, right);
	}
	return (left);
}

t_ast_node	*parse_sequence(t_token **token, t_env **env)
{
	t_ast_node	*left;
	t_ast_node	*right;

	left = NULL;
	right = NULL;
	while (*token && (*token)->type != TOKEN_EOF)
	{
		if ((*token)->type == TOKEN_OPEN_BRACKET)
			left = parse_grouped_commands(token, env);
		else
			left = parse_logical(token, env);
		if (*token && (*token)->type == TOKEN_SEMI)
		{
			*token = (*token)->next;
			right = parse_sequence(token, env);
			left = new_ast_node(TOKEN_SEMI, NULL, left, right);
		}
		else
			break;
	}
	return (left);
}

t_ast_node	*parse_grouped_commands(t_token **token, t_env **env)
{
	t_ast_node	*group;

	if ((*token)->type != TOKEN_OPEN_BRACKET)
	{
		ft_perror("Expected open bracket\n");
		return (NULL);
	}
	*token = (*token)->next;
	if (*token && (*token)->type == TOKEN_CLOSE_BRACKET)
	{
		ft_perror("Empty command group\n");
		*token = (*token)->next;  // Move past the close bracket
		return new_ast_node(TOKEN_GROUP, NULL, NULL, NULL);  // Replace TOKEN_GROUP with your actual token for groups
	}
	group = parse_sequence(token, env);
	if ((*token)->type != TOKEN_CLOSE_BRACKET)
	{
		ft_perror("Expected close bracket\n");
		return (NULL);
	}
	*token = (*token)->next;
	return (group);
}
