/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_hooks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 11:20:03 by aessaber          #+#    #+#             */
/*   Updated: 2025/04/20 15:30:47 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_header.h"

static void	fractol_move(t_fractol *f, double distance, char direction)
{
	double	real_center;
	double	i_center;

	real_center = f->real_max - f->real_min;
	i_center = f->i_max - f->i_min;
	if (direction == 'R')
	{
		f->real_min += real_center * distance;
		f->real_max += real_center * distance;
	}
	else if (direction == 'L')
	{
		f->real_min -= real_center * distance;
		f->real_max -= real_center * distance;
	}
	else if (direction == 'D')
	{
		f->i_min -= i_center * distance;
		f->i_max -= i_center * distance;
	}
	else if (direction == 'U')
	{
		f->i_min += i_center * distance;
		f->i_max += i_center * distance;
	}
}

static void	fractol_color_swap(t_fractol *fractol)
{
	if (fractol->color == COLOR_DEFAULT)
		fractol->color = COLOR_GREEN;
	else if (fractol->color == COLOR_GREEN)
		fractol->color = COLOR_RED;
	else if (fractol->color == COLOR_RED)
		fractol->color = COLOR_BLUE;
	else if (fractol->color == COLOR_BLUE)
		fractol->color = COLOR_FUL;
	else if (fractol->color == COLOR_FUL)
		fractol->color = COLOR_DEFAULT;
}

int	fractol_key_hook(int keycode, t_fractol *fractol)
{
	if (keycode == KEY_ESC)
	{
		fractol_close(fractol);
		return (0);
	}
	else if (keycode == KEY_PLUS)
		fractol_zoom_keyboard(fractol, 0.75);
	else if (keycode == KEY_MINUS)
		fractol_zoom_keyboard(fractol, 1.5);
	else if (keycode == KEY_UP)
		fractol_move(fractol, 0.2, 'U');
	else if (keycode == KEY_DOWN)
		fractol_move(fractol, 0.2, 'D');
	else if (keycode == KEY_LEFT)
		fractol_move(fractol, 0.2, 'L');
	else if (keycode == KEY_RIGHT)
		fractol_move(fractol, 0.2, 'R');
	else if (keycode == KEY_SPACE)
	{
		fractol_color_swap(fractol);
	}
	else
		return (1);
	fractol_render(fractol);
	return (0);
}

int	fractol_mouse_hook(int keycode, int x, int y, t_fractol *fractol)
{
	if (keycode == MOUSE_SCROLL_UP)
		fractol_zoom_mouse(fractol, 0.75, x, y);
	else if (keycode == MOUSE_SCROLL_DOWN)
		fractol_zoom_mouse(fractol, 1.5, x, y);
	else if (keycode == MOUSE_CLICK)
		fractol_color_swap(fractol);
	else
		return (0);
	fractol_render(fractol);
	return (0);
}

