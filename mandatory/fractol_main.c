/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:05:32 by aessaber          #+#    #+#             */
/*   Updated: 2025/04/18 21:04:30 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_header.h"

// libft ----------------------------------------------------------------------/

void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

// clear_exit -----------------------------------------------------------------/

void	fractol_exit(t_fractol *fractol, int exit_type)
{
	if (!fractol)
		exit(exit_type);
	if (fractol->palette)
		free(fractol->palette);
	if (fractol->img_ptr)
		mlx_destroy_image(fractol->mlx_ptr, fractol->img_ptr);
	if (fractol->mlx_win && fractol->mlx_ptr)
		mlx_destroy_window(fractol->mlx_ptr, fractol->mlx_win);
	if (fractol->mlx_ptr)
		free(fractol->mlx_ptr);
	exit(exit_type);
}

// msg_manual -----------------------------------------------------------------/

static void	manual_set_options(void)
{
	ft_putendl_fd("\n\e[3;34m+---- Available Fractals ----+\e[0m\n", 1);
	ft_putendl_fd("Fractal sets:", 1);
	ft_putendl_fd("\t- Mandelbrot", 1);
	ft_putendl_fd("\t- Julia", 1);
	ft_putendl_fd("\n\e[3;36mUsage example:\n\t./fractol Mandelbrot", 1);
	ft_putendl_fd("\e[3m\t./fractol Julia <x> <y>\e[0m", 1);
	ft_putendl_fd("\nx & y are between -2.0 and 2.0,", 1);
	ft_putendl_fd("and must contain a fraction.\n", 1);
	ft_putendl_fd("\e[3;34m+------------------------------+\e[0m", 1);
}

void	manual_exit(t_fractol *fractol)
{
	ft_putendl_fd("\n\e[1;3;4;35m+--------- Fract\e[36m-ol ---------+\e[0m", 1);
	manual_set_options();
	ft_putendl_fd("\n\e[1;3;4;35m+--------------\e[36m--------------+\e[0m", 1);
	fractol_exit(fractol, EXIT_FAILURE);
}

int	msg(char *str, int errno)
{
	ft_putstr_fd("\e[31mFract-ol: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd("\e[0m", STDERR_FILENO);
	return (errno);
}

// fractol_atof --------------------------------------------------------------/

static int	ft_isspace(int c)
{
	return ((c >= '\t' && c <= '\r') || c == ' ');
}

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static void	atof_sign(char *str, int *col, int *sign)
{
	*col = 0;
	*sign = 1;
	while (ft_isspace(str[*col]))
		(*col)++;
	if (str[*col] == '+')
		(*col)++;
	else if (str[*col] == '-')
	{
		*sign = -1;
		(*col)++;
	}
}

double	fractol_atof(t_fractol *fractol, char *str)
{
	int		col;
	int		sign;
	double	res;
	double	fraction;

	atof_sign(str, &col, &sign);
	res = 0;
	while (ft_isdigit(str[col]))
	{
		res = res * 10 + (str[col] - '0');
		col++;
	}
	if (!ft_isdigit(str[col - 1]) || str[col] != '.')
		manual_exit(fractol);
	col++;
	fraction = 0.1;
	while (ft_isdigit(str[col]))
	{
		res += (str[col] - '0') * fraction;
		fraction *= 0.1;
		col++;
	}
	if (str[col] != '\0')
		manual_exit(fractol);
	return (res * sign);
}
// colors ---------------------------------------------------------------------/

static int	interpolation(int color_start, int color_end, double fract)
{
	int	rgb_start[3];
	int	rgb_end[3];

	rgb_start[0] = ((color_start >> 16) & 0xFF);
	rgb_start[1] = ((color_start >> 8) & 0xFF);
	rgb_start[2] = ((color_start >> 0) & 0xFF);
	rgb_end[0] = ((color_end >> 16) & 0xFF);
	rgb_end[1] = ((color_end >> 8) & 0xFF);
	rgb_end[2] = ((color_end >> 0) & 0xFF);
	rgb_start[0] = (rgb_end[0] - rgb_start[0]) * fract + rgb_start[0];
	rgb_start[1] = (rgb_end[1] - rgb_start[1]) * fract + rgb_start[1];
	rgb_start[2] = (rgb_end[2] - rgb_start[2]) * fract + rgb_start[2];
	return (0xFF << 24 | rgb_start[0] << 16 | rgb_start[1] << 8 | rgb_start[2]);
}

void	fractol_monotone(t_fractol *f, int color)
{
	int		i;
	int		j;
	double	fract;
	int		color_start;
	int		color_end;

	color_start = 0x000000;
	color_end = color;
	i = 0;
	while (i < MAX_ITERATIONS)
	{
		j = 0;
		while (j < MAX_ITERATIONS / 2)
		{
			fract = (double)j /(MAX_ITERATIONS / 2);
			f->palette[i + j] = interpolation(color_start, color_end, fract);
			j++;
		}
		color_start = color_end;
		color_end = 0xFFFFFF;
		i += j;
	}
	f->palette[MAX_ITERATIONS - 1] = 0;
}

void	fractol_colorful(t_fractol *f, int colors[4], int num)
{
	int		i;
	int		j;
	int		r;
	double	fract;

	i = 0;
	r = 0;
	while (i < MAX_ITERATIONS)
	{
		j = 0;
		while ((i + j) < MAX_ITERATIONS && j < (MAX_ITERATIONS / (num - 1)))
		{
			fract = (double)j / (MAX_ITERATIONS / (num - 1));
			f->palette[i + j] = interpolation(colors[r], colors[r + 1], fract);
			j++;
		}
		x++;
		i += j;
	}
	f->palette[MAX_ITERATIONS - 1] = 0;
}

// image ----------------------------------------------------------------------/

static	void fractol_image(t_fractol *f)
{
	int		bits_per_pixel;
	int		size_line;
	int		n;

	f->palette = ft_calloc((MAX_ITERATIONS + 1), sizeof(int));
	if (!(f->palette))
		fractol_exit(msg("PALETTE ALLOCATION ERROR", ERROR), f);
	f->img_ptr = mlx_new_image(f->mlx_ptr, RES, RES);
	if (!(f->img_ptr))
		fractol_exit(msg("IMAGE CREATION ERROR", ERROR), f);
	f->buffer = mlx_get_data_addr(f->img_ptr, &bits_per_pixel, &size_line, &n);
	(void)n;
}

void	fractol_refresh(t_fractol *fractol)
{
	if (fractol->mlx_ptr && fractol->img_ptr)
		mlx_destroy_image(fractol->mlx_ptr, fractol->img_ptr);
	if (fractol->palette)
		free(fractol->palette);
	if (fractol->buffer)
		fractol->buffer = NULL;
	fractol_image(fractol);
}

void	fractol_gradiant(t_fractol *fractol)
{
	int	color;

	fractol->color_pattern = (fractol->color_pattern + 1) % 3;
	fractol_refresh(fractol);
	if (fractol->color == 0x000000)
		color = 0x333333;
	else
		color = fractol->color;
	if (fractol->color_pattern == 0)
		fractol_monotone(fractol, color);
	else if (fractol->color_pattern == 1)
		fractol_colorful(fractol, (int [4]){0x000000, color,
			color_shift(fractol->color, 50), 0xFFFFFF}, 4);
	else
		color_shift_striped(fractol);
}

// initialization -------------------------------------------------------------/

void	fractol_clear(t_fractol *fractol)
{
	fractol->set = 0;
	fractol->x = 0.0;
	fractol->y = 0.0;
	fractol->mlx_ptr = NULL;
	fractol->mlx_win = NULL;
	fractol->img_ptr = NULL;
	fractol->real_max = 0;
	fractol->real_min = 0;
	fractol->i_max = 0;
	fractol->i_min = 0;
	fractol->color_pattern = -1;
	// after a fully defined struct
}

void	window_position(t_fractol *f)
{
	if (f->set == MANDELBROT)
	{
		f->real_max = 1.0;
		f->real_min = -2.0;
		f->i_max = -1.5;
		f->i_min = 1.5;
	}
	else if (f->set == JULIA)
	{
		f->real_max = 2.0;
		f->real_min = -2.0;
		f->i_max = -2.0;
		f->i_min = -2.0;
	}
}

void	fractol_initialize(t_fractol *f)
{
	f->mlx_ptr = mlx_init();
	if (!f->mlx_ptr)
		clear_exit(f, msg("MLX INITIALIZATION ERROR", ERROR));
	f->mlx_win = mlx_new_window(f->mlx_ptr, RES, RES, "Fract-ol");
	if (!f->mlx_win)
		clear_exit(f, msg("MLX WINDOW CREATION ERROR", ERROR));
	f->sx = 2.0;
	f->rx = 0.5;
	f->fx = 1.0;
	window_position(f);
	fractol_gradiant(f);
}
// fractal_sets ---------------------------------------------------------------/

int	fractol_mandelbrot(double real_cord, double i_cord)
{
	int		number_of_iterations;
	double	real_z;
	double	i_z;
	double	tmp_i_z;

	real_z = 0;
	i_z = 0;
	number_of_iterations = 0;
	while (number_of_iterations < MAX_ITERATIONS)
	{
		if (((real_z * real_z) + (i_z + i_z)) > 4.0)
			return (number_of_iterations);
		tmp_i_z = (2 * real_z * i_z) + i_cord;
		real_z = (real_z * real_z) - (i_z * i_z) + real_cord;
		i_z = tmp_i_z;
		number_of_iterations++;
	}
	return (number_of_iterations);
}

// rendering ------------------------------------------------------------------/

static int	calculate_fractal(t_fractol *fractol, double real_p, double i_p)
{
	int	number_of_iterations;

	if (fractol->set == MANDELBROT)
		number_of_iterations = fractol_mandelbrot(real_p, i_p);
	else if (fractol->set == JULIA)
		number_of_iterations = fractol_julia(fractol, real_p, i_p);//do
	return (number_of_iterations);
}

void	fractol_render(t_fractol *f)
{
	int		x;
	int		y;
	double	r_p;
	double	i_p;
	int		number_of_iterations;

	mlx_clear_window(f->mlx_ptr, f->mlx_win);
	y = -1;
	while (++y < RES)
	{
		x = -1;
		while (++x < RES)
		{
			r_p = f->real_min + (double)x * (f->real_max - f->real_min) / RES;
			i_p = f->i_max + (double)y * (f->i_min - f->i_max) / RES;
			number_of_iterations = calculate_fractal(f, r_p, i_p);
			//set_pixel_color(f, x, y, f->palette[number_of_iterations]);
		}
	}
	mlx_put_image_to_window(f->mlx_ptr, f->mlx_win, f->img_ptr, 0, 0);
}

// main -----------------------------------------------------------------------/

static int	set_is_correct(char *str_av, char *str_set)
{
	int	col;

	col = 0;
	while (str_av[col])
	{
		if (str_av[col] >= 'A' && str_av[col] <= 'Z')
			str_av[col] += 32;
		if (str_av[col] != str_set[col])
			return (FALSE);
		col++;
	}
	return (str_set[col] == '\0');
}

static void	args_parcing(t_fractol *fractol, int ac, char **av)
{
	
	if (ac == 3)
		manual_exit(fractol);
	if (set_is_correct(av[1], "mandelbrot"))
		fractol->set = MANDELBROT;
	else if (set_is_correct(av[1], "julia"))
		fractol->set = JULIA;
	else
		manual_exit(fractol);
	if (fractol->set == MANDELBROT && ac == 2)
		return ;
	else if (fractol->set == JULIA && ac == 4)
	{
		fractol->x = fractol_atof(fractol, av[2]);
		fractol->y = fractol_atof(fractol, av[3]);
		if (fractol->x < -2.0 || fractol->x > 2.0)
			manual_exit(fractol);
		if (fractol->y < -2.0 || fractol->y > 2.0)
			manual_exit(fractol);
	}
	else
		manual_exit(fractol);
}

int	main(int ac, char **av)
{
	t_fractol	fractol;

	if (ac == 1)
		manual_exit(&fractol);
	fractol_clear(&fractol);
	args_parcing(&fractol, ac, av);
	fractol_initialize(&fractol);
	fractol_render(&fractol);
}
