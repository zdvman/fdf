/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 14:50:51 by dzuiev            #+#    #+#             */
/*   Updated: 2024/01/15 16:22:56 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int	ft_issign(int c)
{
	return (c == '+' || c == '-');
}

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_isnumber(char *arg)
{
	int	i;
	
	i = 0;
	if (ft_issign(arg[i]) && arg[i + 1] != '\0')
		i++;
	while (arg[i] && ft_isdigit(arg[i]))
		i++;
	if(arg[i] != '\0' && !ft_isdigit(arg[i]))
		return (0);
	return (1);
}

static int	ft_nbr_strcmp(const char *s1, const char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (s1[i] == '+')
	{
		if (s2[j] != '+')
			i++;
	}
	else
	{
		if (s2[j] == '+')
			j++;
	}
	while (s1[i] != '\0' && s2[j] != '\0' && s1[i] == s2[j])
	{
		i++;
		j++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[j]);
}

static int	ft_duplicates_presented(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 1;
		while (argv[j])
		{
			if (j != i && ft_nbr_strcmp(argv[i], argv[j]) == 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	ft_iszero(char *arg)
{
	int	i;

	i = 0;
	if (ft_issign(arg[i]))
		i++;
	while (arg[i] && arg[i] == '0')
		i++;
	if (arg[i] != '\0')
		return (0);
	return (1);
}

static int	ft_isempty(char *arg)
{
	return (arg[0] == '\0'); 
}

int	ft_input_isvalid(char **argv)
{
	int	i;
	int	count_zeros;

	i = 1;
	count_zeros = 0;
	while (argv[i])
	{
		if (!ft_isnumber(argv[i]) || ft_isempty(argv[i]))
			return (0);
		count_zeros += ft_iszero(argv[i]);
		i++;
	}
	if (count_zeros > 1)
		return (0);
	if (ft_duplicates_presented(argv))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{

	if (argc < 2)
	{
		write(2, "Error\n", 6);	
		return (-1);
	}
	else
		{
			if (!ft_input_isvalid(argv))
			{
				write(2, "Error\n", 6);
				return (-1);
			}
			else
			{
				if (argc == 2)
				       return (0);
				else
					write(1, "OK\n", 3);
			}
		}
	return (0);
}
