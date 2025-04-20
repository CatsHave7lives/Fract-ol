/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 11:20:03 by aessaber          #+#    #+#             */
/*   Updated: 2025/04/20 08:28:52 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_header.h"

void	fractol_exit(t_fractol *fractol, int exit_type)
{
	if (!fractol)
		exit(exit_type);
	if (fractol->img_ptr)
		mlx_destroy_image(fractol->mlx_ptr, fractol->img_ptr);
	if (fractol->mlx_win && fractol->mlx_ptr)
		mlx_destroy_window(fractol->mlx_ptr, fractol->mlx_win);
	exit(exit_type);
}

int	msg(char *str, int errno)
{
	ft_putstr_fd("\e[31mFract-ol: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd("\e[0m", STDERR_FILENO);
	return (errno);
}

int	fractol_close(t_fractol *mlx)
{
	fractol_exit(mlx, 0);
	return (0);
}
