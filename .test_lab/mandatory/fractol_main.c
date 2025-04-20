/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:05:32 by aessaber          #+#    #+#             */
/*   Updated: 2025/04/20 15:34:55 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_header.h"

static void	fractol_struct_init(t_fractol *fractol)
{
	fractol->set = 0;
	fractol->x = 0.0;
	fractol->y = 0.0;
	fractol->mlx_ptr = NULL;
	fractol->mlx_win = NULL;
	fractol->img_ptr = NULL;
	fractol->pixels = NULL;
	fractol->real_max = 0;
	fractol->real_min = 0;
	fractol->i_max = 0;
	fractol->i_min = 0;
	fractol->color = COLOR_DEFAULT;
	fractol->color_pattern = -1;
	fractol->zoom_factor = 1.0;
}

void f(void)
{
	system("leaks a.out");
}

int	main(int ac, char **av)
{
	// atexit(f);
	t_fractol	fractol;

	if (ac != 2 && ac != 4)
		fractol_manual_exit(&fractol);
	fractol_struct_init(&fractol);
	fractol_args_parcing(&fractol, ac, av);
	fractol_initialization(&fractol);
	fractol_render(&fractol);
	mlx_hook(fractol.mlx_win, CLOSE, 0, fractol_close, &fractol);
	mlx_key_hook(fractol.mlx_win, fractol_key_hook, &fractol);
	mlx_mouse_hook(fractol.mlx_win, fractol_mouse_hook, &fractol);
	mlx_loop(fractol.mlx_ptr);
}
