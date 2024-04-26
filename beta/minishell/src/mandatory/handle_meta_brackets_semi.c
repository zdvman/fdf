/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_meta_brackets_semi.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 09:16:32 by dzuiev            #+#    #+#             */
/*   Updated: 2024/04/26 09:17:07 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_semicolon(t_env **env, char **input)
{
	add_token(TOKEN_SEMI, ft_strdup(";"),
		ft_isspace(*(*input + 1)), env);
	(*input)++;
}

void	handle_open_bracket(t_env **env, char **input)
{
	add_token(TOKEN_OPEN_BRACKET, ft_strdup("("),
		ft_isspace(*(*input + 1)), env);
	(*input)++;
}

void	handle_close_bracket(t_env **env, char **input)
{
	add_token(TOKEN_CLOSE_BRACKET, ft_strdup(")"),
		ft_isspace(*(*input + 1)), env);
	(*input)++;
}
