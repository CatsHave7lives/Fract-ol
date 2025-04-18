/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:05:32 by aessaber          #+#    #+#             */
/*   Updated: 2025/04/15 18:03:54 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol_header.h>

// main

static int	set_is_correct(char *str_av, char *str_set)
{
	int	col;

	col = 0;
	while (str_av[col] && str_set)
	{
		if (str_av[col] != str_set[col])
			return (FALSE);
		col++;
	}
	if (str_set[col] != '\0')
		return (FALSE);
	return (TRUE);
}

static void	get_fractal_set(t_fractol *fractol, char **av)
{
	if (set_is_correct(av[1], "mandelbrot"));
}

static void	args_parcing(t_fractol *fractol, int ac, char av)
{
	get_fractal_set(fractol, av);
}

int	main(int ac, char **av)
{
	t_fractol	fractol;

	if (ac = 1)
		fractol_manual(&fractol);
	fractol_clean(&fractol);
	args_parcing(&fractol, ac, av);
}
