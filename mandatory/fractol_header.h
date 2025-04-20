/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_header.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:07:30 by aessaber          #+#    #+#             */
/*   Updated: 2025/04/20 14:22:40 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_HEADER_H
# define FRACTOL_HEADER_H

# include <mlx.h>

# include <unistd.h>
# include <stdlib.h>

// keys
# define CLOSE 17
# define KEY_ESC      53
# define KEY_PLUS     69
# define KEY_MINUS    78
# define KEY_UP       126
# define KEY_DOWN     125
# define KEY_LEFT     123
# define KEY_RIGHT    124
# define KEY_SPACE    49
# define MOUSE_CLICK   1
# define MOUSE_SCROLL_UP   4
# define MOUSE_SCROLL_DOWN 5

// fractol
# define RES 600
# define MAX_ITERATIONS 100
# define MIN_ZOOM 0.0000000000001
# define MAX_ZOOM 10.0
# define TRUE 1
# define FALSE 0
# define ERROR 1
# define MANDELBROT 1
# define JULIA 2

//colors
# define COLOR_DEFAULT 0x080808
# define COLOR_GREEN 0x020402
# define COLOR_RED 0x040001
# define COLOR_BLUE 0x020204
# define COLOR_FUL 0xA6E1FA

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
	int		color;
	double	zoom_factor;
}	t_fractol;

// utils_libft.c
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	*ft_calloc(size_t count, size_t size);

// utils_exit.c
void	fractol_exit(t_fractol *fractol, int exit_type);
int		msg(char *str, int errno);
int		fractol_close(t_fractol *mlx);

// fractol_manual_exit.c
void	fractol_manual_exit(t_fractol *fractol);

// fractol_initialization.c
void	fractol_initialization(t_fractol *fractol);

// fractol_sets.c
int		fractol_mandelbrot(double real_cord, double i_cord);
int		fractol_julia(t_fractol *fractol, double real_z, double i_z);

// fractol_render.c
void	fractol_render(t_fractol *f);

// fractol_atof.c
double	fractol_atof(t_fractol *fractol, char *str);

// fractol_args_parcing.c
void	fractol_args_parcing(t_fractol *fractol, int ac, char **av);

// fractol_hooks.c
int	fractol_key_hook(int keycode, t_fractol *fractol);
int	fractol_mouse_hook(int keycode, int x, int y, t_fractol *fractol);

#endif