/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:39:53 by dzuiev            #+#    #+#             */
/*   Updated: 2024/04/18 18:02:41 by dzuiev           ###   ########.fr       */
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

char	new_current_quote(char current_quote, char c)
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
		if (input[i] == '\\' && (input[i + 1] == '\'' || input[i + 1] == '\"'))
		{
			i++;
			current_quote = new_current_quote(current_quote, input[i]);
		}
		else if (input[i] == '\'' || input[i] == '\"')
		{
			current_quote = new_current_quote(current_quote, input[i]);
		}
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

int	main(void)
{
	t_token	*tokens;
	t_token	*current;
	char	*input;

	tokens = NULL;
	printf("\033[?12h");
	set_sig_actions();
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
			// tokenize(input, &tokens);
		}
		if (input)
			free(input);
	}
	current = tokens;
	while (current)
	{
		printf("tokens->type: %d; tokens->value: %s\n", current->type, current->value);
		current = current->next;
	}
	printf("\033[?12l");
	rl_clear_history();
	cleanup(&tokens, 0);
	return (0);
}
