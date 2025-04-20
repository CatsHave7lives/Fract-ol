/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_initialization.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 11:20:03 by aessaber          #+#    #+#             */
/*   Updated: 2025/04/20 15:20:39 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_header.h"

static	void fractol_image(t_fractol *fractol)
{
	fractol->img_ptr = mlx_new_image(fractol->mlx_ptr, RES, RES);
	if (!(fractol->img_ptr))
		fractol_exit(fractol, msg("IMAGE CREATION ERROR", ERROR));
	fractol->pixels = mlx_get_data_addr(fractol->img_ptr,
			&fractol->bits_per_pixel, &fractol->size_line, &fractol->n);
}
static void	window_position(t_fractol *fractol)
{
	if (fractol->set == MANDELBROT)
	{
		fractol->real_max = 1.0;
		fractol->real_min = -2.0;
		fractol->i_max = -1.5;
		fractol->i_min = 1.5;
	}
	else if (fractol->set == JULIA)
	{
		fractol->real_max = 2.0;
		fractol->real_min = -2.0;
		fractol->i_max = -2.0;
		fractol->i_min = 2.0;
	}
}

void	fractol_initialization(t_fractol *fractol)
{
	fractol->mlx_ptr = mlx_init();
	if (!fractol->mlx_ptr)
		fractol_exit(fractol, msg("MLX INITIALIZATION ERROR", ERROR));
	fractol->mlx_win = mlx_new_window(fractol->mlx_ptr, RES, RES, "Fract-ol");
	if (!fractol->mlx_win)
		fractol_exit(fractol, msg("MLX WINDOW CREATION ERROR", ERROR));
	window_position(fractol);
	fractol_image(fractol);
}
