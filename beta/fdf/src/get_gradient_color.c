/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_gradient_color.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzuiev <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:11:14 by dzuiev            #+#    #+#             */
/*   Updated: 2024/03/14 13:23:35 by dzuiev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libfdf.h"

// Функция для линейной интерполяции между двумя значениями
static float	lerp(float start, float end, float t)
{
	return (start + t * (end - start));
}

static int	grad_red(int start, int end, float t)
{
	return (ft_round(lerp((start >> 16) & 0xFF, (end >> 16) & 0xFF, t)));
}

static int	grad_green(int start, int end, float t)
{
	return (ft_round(lerp((start >> 8) & 0xFF, (end >> 8) & 0xFF, t)));
}

static int	grad_blue(int start, int end, float t)
{
	return (ft_round(lerp(start & 0xFF, end & 0xFF, t)));
}

// Функция для получения цвета градиента между двумя цветами
unsigned int	get_gradient_color(unsigned int startColor,
					unsigned int endColor, float t)
{
	int	red;
	int	green;
	int	blue;

	red = grad_red(startColor, endColor, t);
	green = grad_green(startColor, endColor, t);
	blue = grad_blue(startColor, endColor, t);
	return ((red << 16) | (green << 8) | blue);
}
