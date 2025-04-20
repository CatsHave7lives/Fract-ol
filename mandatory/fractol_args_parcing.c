/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_args_parcing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 11:20:03 by aessaber          #+#    #+#             */
/*   Updated: 2025/04/20 08:42:59 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_header.h"

static int	set_is_correct(char *str_av, char *str_set)
{
	int	col;

	col = 0;
	while (str_av[col])
	{
		if (str_av[col] >= 'A' && str_av[col] <= 'Z')
			str_av[col] += 32;
		if (str_av[col] != str_set[col])
			return (FALSE);
		col++;
	}
	return (str_set[col] == '\0');
}

static void fractol_get_set(t_fractol *fractol, char *set)
{
	if (set_is_correct(set, "mandelbrot"))
		fractol->set = MANDELBROT;
	else if (set_is_correct(set, "julia"))
		fractol->set = JULIA;
	else
		fractol_manual_exit(fractol);
}

void	fractol_args_parcing(t_fractol *fractol, int ac, char **av)
{
	if (ac == 3)
		fractol_manual_exit(fractol);
	fractol_get_set(fractol, av[1]);
	if (fractol->set == MANDELBROT && ac == 2)
		return ;
	else if (fractol->set == JULIA && ac == 4)
	{
		fractol->x = fractol_atof(fractol, av[2]);
		fractol->y = fractol_atof(fractol, av[3]);
		if (fractol->x < -2.0 || fractol->x > 2.0)
			fractol_manual_exit(fractol);
		if (fractol->y < -2.0 || fractol->y > 2.0)
			fractol_manual_exit(fractol);
	}
	else
		fractol_manual_exit(fractol);
}
