/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:00:30 by dzuiev            #+#    #+#             */
/*   Updated: 2024/04/26 18:10:54 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static void	execute_command(t_env **env, t_ast_node *node)
// {
// 	char	*path;
// 	char	**args;
// 	int		status;

// 	path = find_executable(node->args[0], (*env)->path);
// 	if (path == NULL)
// 	{
// 		ft_printf("minishell: %s: command not found\n", node->args[0]);
// 		(*env)->exit_status = 127;
// 		return ;
// 	}
// 	args = ft_array_dup(node->args);
// 	status = execute(path, args, (*env)->envp);
// 	free(path);
// 	ft_array_free(args);
// 	(*env)->exit_status = status;
// }
