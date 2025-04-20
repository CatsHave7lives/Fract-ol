/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_zoom.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 11:20:03 by aessaber          #+#    #+#             */
/*   Updated: 2025/04/20 15:29:54 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_header.h"

void	fractol_zoom_keyboard(t_fractol *f, double zoom)
{
	double	real_center;
	double	i_center;
	double new_zoom_factor;

	new_zoom_factor = f->zoom_factor * zoom;
	if ((zoom < 1.0 && new_zoom_factor < MIN_ZOOM)
		|| (zoom > 1.0 && new_zoom_factor > MAX_ZOOM))
		return;
	f->zoom_factor = new_zoom_factor;
	real_center = f->real_min - f->real_max;
	i_center = f->i_max - f->i_min;
	f->real_max = f->real_max + (real_center - zoom * real_center) / 2;
	f->real_min = f->real_max + zoom * real_center;
	f->i_min = f->i_min + (i_center - zoom * i_center) / 2;
	f->i_max = f->i_min + zoom * i_center;
}

void fractol_zoom_mouse(t_fractol *f, double zoom, int x, int y)
{
	double mouse_re;
	double mouse_im;
	double new_width;
	double new_height;
	double new_zoom_factor;

	new_zoom_factor = f->zoom_factor * zoom;
	if ((zoom < 1.0 && new_zoom_factor < MIN_ZOOM)
		|| (zoom > 1.0 && new_zoom_factor > MAX_ZOOM))
		return;
	f->zoom_factor = new_zoom_factor;
	mouse_re = f->real_min + (f->real_max - f->real_min) * x / (double)RES;
	mouse_im = f->i_max - (f->i_max - f->i_min) * y / (double)RES;
	new_width = (f->real_max - f->real_min) * zoom;
	new_height = (f->i_max - f->i_min) * zoom;
	f->real_min = mouse_re - (x / (double)RES) * new_width;
	f->real_max = f->real_min + new_width;
	f->i_max = mouse_im + (y / (double)RES) * new_height;
	f->i_min = f->i_max - new_height;
}
