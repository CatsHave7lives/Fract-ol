/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_manual_exit.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 11:20:03 by aessaber          #+#    #+#             */
/*   Updated: 2025/04/20 06:06:50 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_header.h"

static void	manual_set_options(void)
{
	ft_putendl_fd("\n\e[3;34m+---- Available Fractals ----+\e[0m\n", 1);
	ft_putendl_fd("Fractal sets:", 1);
	ft_putendl_fd("\t- Mandelbrot", 1);
	ft_putendl_fd("\t- Julia", 1);
	ft_putendl_fd("\n\e[3;36mUsage example:\n\t./fractol Mandelbrot", 1);
	ft_putendl_fd("\e[3m\t./fractol Julia <x> <y>\e[0m", 1);
	ft_putendl_fd("\nx & y are between -2.0 and 2.0,", 1);
	ft_putendl_fd("and must contain a fraction.\n", 1);
	ft_putendl_fd("\e[3;34m+----------------------------+\e[0m", 1);
}

void	fractol_manual_exit(t_fractol *fractol)
{
	ft_putendl_fd("\n\e[1;3;35m+--------- Fract\e[36m-ol ---------+\e[0m", 1);
	manual_set_options();
	ft_putendl_fd("\n\e[1;3;35m+--------------\e[36m--------------+\e[0m", 1);
	fractol_exit(fractol, EXIT_FAILURE);
}
