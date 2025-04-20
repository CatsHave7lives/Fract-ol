/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 11:20:03 by aessaber          #+#    #+#             */
/*   Updated: 2025/04/20 15:23:08 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_header.h"

static int	calculate_fractal(t_fractol *fractol, double real_p, double i_p)
{
	int	iteration_num;

	if (fractol->set == MANDELBROT)
		iteration_num = fractol_mandelbrot(real_p, i_p);
	else if (fractol->set == JULIA)
		iteration_num = fractol_julia(fractol, real_p, i_p);
	return (iteration_num);
}

static void	put_color(int x, int y,t_fractol *fractal, int next_color)
{
	int offset;

	offset = (y * fractal->size_line) + (x * (fractal->bits_per_pixel / 8));
	*(unsigned int *)(fractal->pixels + offset) = next_color;
}

static void	fractol_pixel_color(t_fractol *fractol, int x, int y, int color)
{
	int next_color;

	next_color = fractol->color * color;
	put_color(x, y, fractol, next_color);
}

void	fractol_render(t_fractol *f)
{
	int		x;
	int		y;
	double	r_p;
	double	i_p;
	int		iteration_num;

	mlx_clear_window(f->mlx_ptr, f->mlx_win);
	y = -1;
	while (++y < RES)
	{
		x = -1;
		while (++x < RES)
		{
			r_p = f->real_min + (double)x * (f->real_max - f->real_min) / RES;
			i_p = f->i_max + (double)y * (f->i_min - f->i_max) / RES;
			iteration_num = calculate_fractal(f, r_p, i_p);
			if ((iteration_num < MAX_ITERATIONS)
				&& (r_p * r_p) + (i_p * i_p) < 4)
				fractol_pixel_color(f, x, y, iteration_num);
			else 
				put_color(x, y, f, 0x000000);
		}
	}
	mlx_put_image_to_window(f->mlx_ptr, f->mlx_win, f->img_ptr, 0, 0);
}
