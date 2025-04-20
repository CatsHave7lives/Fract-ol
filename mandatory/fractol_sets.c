/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_sets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 11:20:03 by aessaber          #+#    #+#             */
/*   Updated: 2025/04/20 06:18:52 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_header.h"

int	fractol_mandelbrot(double real_cord, double i_cord)
{
	int		iteration_num;
	double	real_z;
	double	i_z;
	double	tmp_i_z;

	real_z = 0;
	i_z = 0;
	iteration_num = 0;
	while (iteration_num < MAX_ITERATIONS)
	{
		tmp_i_z = (2 * real_z * i_z) + i_cord;
		real_z = (real_z * real_z) - (i_z * i_z) + real_cord;
		i_z = tmp_i_z;
		if (((real_z * real_z) + (i_z + i_z)) > 4.0)
			return (iteration_num);
		iteration_num++;
	}
	return (iteration_num);
}

int	fractol_julia(t_fractol *fractol, double real_z, double i_z)
{
	int		n;
	double	tmp;

	n = 0;
	while (n < MAX_ITERATIONS)
	{
		tmp = 2 * real_z * i_z + fractol->y;
		real_z = real_z * real_z - i_z * i_z + fractol->x;
		i_z = tmp;
		if ((i_z * i_z + real_z * real_z) > 4.0)
			break ;
		n++;
	}
	return (n);
}
