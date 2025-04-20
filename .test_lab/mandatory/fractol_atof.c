/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_atof.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 11:20:03 by aessaber          #+#    #+#             */
/*   Updated: 2025/04/20 15:23:34 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_header.h"

static void	atof_integer(char *str, int *col, int *sign, double *res)
{
	*col = 0;
	*sign = 1;
	*res = 0;
	while ((str[*col] >= '\t' && str[*col] <= '\r') || str[*col] == ' ')
		(*col)++;
	if (str[*col] == '+')
		(*col)++;
	else if (str[*col] == '-')
	{
		*sign = -1;
		(*col)++;
	}
	while (str[*col] >= '0' && str[*col] <= '9')
	{
		*res = *res * 10 + (str[*col] - '0');
		(*col)++;
	}
}

double	fractol_atof(t_fractol *fractol, char *str)
{
	int		col;
	int		sign;
	double	res;
	double	fraction;

	if (!str[0])
		fractol_manual_exit(fractol);
	atof_integer(str, &col, &sign, &res);
	if (!str[col])
		return (res * sign);
	if (str[col] != '.')
		fractol_manual_exit(fractol);
	col++;
	fraction = 0.1;
	while (str[col] >= '0' && str[col] <= '9')
	{
		res += (str[col] - '0') * fraction;
		fraction *= 0.1;
		col++;
	}
	while ((str[col] >= '\t' && str[col] <= '\r') || str[col] == ' ')
		(col)++;
	if (str[col] != '\0')
		fractol_manual_exit(fractol);
	return (res * sign);
}
