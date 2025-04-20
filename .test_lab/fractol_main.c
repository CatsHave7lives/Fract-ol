/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:05:32 by aessaber          #+#    #+#             */
/*   Updated: 2025/04/20 16:21:41 by aessaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_header.h"

// // utils_libft ----------------------------------------------------------------------/

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

void	*ft_calloc(size_t count, size_t size)
{
	void	*res;
	size_t	col;
	size_t	len;

	len = count * size;
	if (size != 0 && len / size != count)
		return (NULL); 
	res = malloc(len);
	if (!res)
		return (NULL);
	col = 0;
	while (col < len)
	{
		((unsigned char *)res)[col] = '\0';
		col++;
	}
	return (res);
}

// utils_exit ----------------------------------------------------------------------/

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

// fractol_manual_exit --------------------------------------------------------/

static void	manual_set_options(void)
{
	ft_putendl_fd("\n\e[3;34m+---- Available Fractals ----+\e[0m\n", 1);
	ft_putendl_fd("Fractal sets:", 1);
	ft_putendl_fd("\t- Mandelbrot", 1);
	ft_putendl_fd("\t- Julia", 1);
	ft_putendl_fd("\n\e[3;36mUsage example:\n\t./fractol mandelbrot", 1);
	ft_putendl_fd("\t./fractol MANDELBROT", 1);
	ft_putendl_fd("\t./fractol Julia <x> <y>\e[0m", 1);
	ft_putendl_fd("\nx & y are between -2.0 and 2.0,", 1);
	ft_putendl_fd("and can be written in various ways like:", 1);
	ft_putendl_fd("\t\e[3;36m\"2\" \"-1.\" \"0.1\", \"-.1\"\e[0m", 1);
	ft_putendl_fd("note: typing \".\" only, will be read as \"0.0\"", 1);
	ft_putendl_fd("\e[3;34m+----------------------------+\e[0m", 1);
}

void	fractol_manual_exit(t_fractol *fractol)
{
	ft_putendl_fd("\n\e[1;3;35m+--------- Fract\e[36m-ol ---------+\e[0m", 1);
	manual_set_options();
	ft_putendl_fd("\n\e[1;3;35m+--------------\e[36m--------------+\e[0m", 1);
	fractol_exit(fractol, EXIT_FAILURE);
}

// fractol_initialization -----------------------------------------------------/

static	void fractol_image(t_fractol *fractol)
{
	fractol->img_ptr = mlx_new_image(fractol->mlx_ptr, RES, RES);
	if (!(fractol->img_ptr))
		fractol_exit(fractol, msg("IMAGE CREATION ERROR", ERROR));
	fractol->pixels = mlx_get_data_addr(fractol->img_ptr,
			&fractol->bits_per_pixel, &fractol->size_line, &fractol->n);
}
static void	window_position(t_fractol *fractol)
{
	if (fractol->set == MANDELBROT)
	{
		fractol->real_max = 1.0;
		fractol->real_min = -2.0;
		fractol->i_max = -1.5;
		fractol->i_min = 1.5;
	}
	else if (fractol->set == JULIA)
	{
		fractol->real_max = 2.0;
		fractol->real_min = -2.0;
		fractol->i_max = -2.0;
		fractol->i_min = 2.0;
	}
}

void	fractol_initialization(t_fractol *fractol)
{
	fractol->mlx_ptr = mlx_init();
	if (!fractol->mlx_ptr)
		fractol_exit(fractol, msg("MLX INITIALIZATION ERROR", ERROR));
	fractol->mlx_win = mlx_new_window(fractol->mlx_ptr, RES, RES, "Fract-ol");
	if (!fractol->mlx_win)
		fractol_exit(fractol, msg("MLX WINDOW CREATION ERROR", ERROR));
	window_position(fractol);
	fractol_image(fractol);
}

// fractol_sets -------------------------------------------------------------/

int	fractol_mandelbrot(double real_cord, double i_cord)
{
	int		iteration_num;
	double	real_z;
	double	i_z;
	double	tmp_i_z;

	real_z = 0;
	i_z = 0;
	iteration_num = 0;
	while (iteration_num < MAX_ITERATIONS)
	{
		tmp_i_z = (2 * real_z * i_z) + i_cord;
		real_z = (real_z * real_z) - (i_z * i_z) + real_cord;
		i_z = tmp_i_z;
		if (((real_z * real_z) + (i_z * i_z)) > 4.0)
			return (iteration_num);
		iteration_num++;
	}
	return (iteration_num);
}

int	fractol_julia(t_fractol *fractol, double real_z, double i_z)
{
	int		n;
	double	tmp;

	n = 0;
	while (n < MAX_ITERATIONS)
	{
		tmp = 2 * real_z * i_z + fractol->y;
		real_z = real_z * real_z - i_z * i_z + fractol->x;
		i_z = tmp;
		if ((i_z * i_z + real_z * real_z) > 4.0)
			break ;
		n++;
	}
	return (n);
}

// fractol_render -------------------------------------------------------------/

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

// fractol_atof -----------------------------------------------------------------------/

static void	atof_integer(char *str, int *col, int *sign, double *res)
{
	*col = 0;
	*sign = 1;
	*res = 0;
	while ((str[*col] >= '\t' && str[*col] <= '\r') || str[*col] == ' ')
		(*col)++;
	if (str[*col] == '+')
		(*col)++;
	else if (str[*col] == '-')
	{
		*sign = -1;
		(*col)++;
	}
	while (str[*col] >= '0' && str[*col] <= '9')
	{
		*res = *res * 10 + (str[*col] - '0');
		(*col)++;
	}
}

double	fractol_atof(t_fractol *fractol, char *str)
{
	int		col;
	int		sign;
	double	res;
	double	fraction;

	if (!str[0])
		fractol_manual_exit(fractol);
	atof_integer(str, &col, &sign, &res);
	if (!str[col])
		return (res * sign);
	if (str[col] != '.')
		fractol_manual_exit(fractol);
	col++;
	fraction = 0.1;
	while (str[col] >= '0' && str[col] <= '9')
	{
		res += (str[col] - '0') * fraction;
		fraction *= 0.1;
		col++;
	}
	while ((str[col] >= '\t' && str[col] <= '\r') || str[col] == ' ')
		(col)++;
	if (str[col] != '\0')
		fractol_manual_exit(fractol);
	return (res * sign);
}

// fractol_args_parcing -------------------------------------------------------/

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

static void fractol_get_set(t_fractol *fractol, char *set)
{
	if (set_is_correct(set, "mandelbrot"))
		fractol->set = MANDELBROT;
	else if (set_is_correct(set, "julia"))
		fractol->set = JULIA;
	else
		fractol_manual_exit(fractol);
}

void	fractol_args_parcing(t_fractol *fractol, int ac, char **av)
{
	if (ac == 3)
		fractol_manual_exit(fractol);
	fractol_get_set(fractol, av[1]);
	if (fractol->set == MANDELBROT && ac == 2)
		return ;
	else if (fractol->set == JULIA && ac == 4)
	{
		fractol->x = fractol_atof(fractol, av[2]);
		fractol->y = fractol_atof(fractol, av[3]);
		if (fractol->x < -2.0 || fractol->x > 2.0)
			fractol_manual_exit(fractol);
		if (fractol->y < -2.0 || fractol->y > 2.0)
			fractol_manual_exit(fractol);
	}
	else
		fractol_manual_exit(fractol);
}

// fractol_zoom ---------------------------------------------------------------/

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

// fractol_hooks ---------------------------------------------------------------/

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

// main -----------------------------------------------------------------------/

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
