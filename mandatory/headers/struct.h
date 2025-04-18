/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:16:22 by aessaber          #+#    #+#             */
/*   Updated: 2025/04/18 06:34:50 by aessaber         ###   ########.fr       */
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
	char	*buffer;
	double	real_max;
	double	real_min;
	double	i_max;
	double	i_min;
	int		color_pattern;
	int		*palette;
	int		color;
}	t_fractol;

#endif