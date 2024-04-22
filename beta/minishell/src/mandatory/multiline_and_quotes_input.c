/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiline_and_quotes_input.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:21:10 by dzuiev            #+#    #+#             */
/*   Updated: 2024/04/22 12:56:44 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	new_current_quote(char current_quote, char c)
{
	if (current_quote == 0)
	{
		if (c == '\'' || c == '\"')
			return (c);
	}
	else if (current_quote == c)
		return (0);
	return (current_quote);
}

int	is_quote_open(const char *input)
{
	char	current_quote;
	int		i;

	i = 0;
	current_quote = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\\' && (input[i + 1] == current_quote))
			i++;
		else if ((input[i] == '\'' || input[i] == '\"')
			&& (i == 0 || input[i - 1] != '\\'))
			current_quote = new_current_quote(current_quote, input[i]);
		i++;
	}
	return (current_quote != 0);
}

char	*read_multiline(void)
{
	char	*line;
	char	*multiline;
	char	*temp;

	line = readline("minishell> ");
	if (!line)
		return (NULL);
	multiline = ft_strdup(line);
	free(line);
	while (is_quote_open(multiline))
	{
		line = readline("> ");
		if (!line)
		{
			free(multiline);
			return (NULL);
		}
		temp = ft_strjoin(multiline, "\n");
		free(multiline);
		multiline = ft_strjoin(temp, line);
		free(temp);
		free(line);
	}
	return (multiline);
}
