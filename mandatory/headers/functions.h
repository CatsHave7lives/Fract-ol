/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 06:00:24 by aessaber          #+#    #+#             */
/*   Updated: 2025/04/19 06:11:00 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include <unistd.h>
# include <stdlib.h>
# include "struct.h"

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	*ft_calloc(size_t count, size_t size);
void	fractol_exit(t_fractol *fractol, int exit_type);
int		msg(char *str, int errno);
void	fractol_manual_exit(t_fractol *fractol);
int		interpolation(int color_start, int color_end, double fract);
int		get_color_percent(int fractol_color, double percent);
void	fill_color_stripe(t_fractol *fractol, int color, int stripe);
void	fractol_striped(t_fractol *fractol);
void	fractol_colorful(t_fractol *fractol, int colors[4], int num);
void	fractol_color_shift(t_fractol *fractol);
void	window_position(t_fractol *fractol);
void	fractol_initialization(t_fractol *fractol);
void	fractol_render(t_fractol *f);
void	fractol_args_parcing(t_fractol *fractol, int ac, char **av);

#endif