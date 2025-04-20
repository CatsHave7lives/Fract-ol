/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:16:22 by aessaber          #+#    #+#             */
/*   Updated: 2025/04/20 06:10:11 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_fractol
{
	int		set;
	double	x;
	double	y;
	void	*mlx_ptr;
	void	*mlx_win;
	void	*img_ptr;
	char	*pixels;
	double	real_max;
	double	real_min;
	double	i_max;
	double	i_min;
	int		color_pattern;
	int		bits_per_pixel;
	int		size_line;
	int		n;
	int		*palette;
	int		color;
}	t_fractol;

#endif