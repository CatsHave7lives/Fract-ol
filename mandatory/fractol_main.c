/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessaber <aessaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:05:32 by aessaber          #+#    #+#             */
/*   Updated: 2025/04/19 12:58:00 by aessaber         ###   ########.fr       */
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

// utils ----------------------------------------------------------------------/

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

// fractol_manual_exit ----------------------------------------------------------------/

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

void	fractol_manual_exit(t_fractol *fractol)
{
	ft_putendl_fd("\n\e[1;3;4;35m+--------- Fract\e[36m-ol ---------+\e[0m", 1);
	manual_set_options();
	ft_putendl_fd("\n\e[1;3;4;35m+--------------\e[36m--------------+\e[0m", 1);
	fractol_exit(fractol, EXIT_FAILURE);
}

// utils_color_shift ----------------------------------------------------------/

// int	interpolation(int color_start, int color_end, double fract)
// {
// 	int	rgb_start[3];
// 	int	rgb_end[3];

// 	rgb_start[0] = ((color_start >> 16) & 0xFF);
// 	rgb_start[1] = ((color_start >> 8) & 0xFF);
// 	rgb_start[2] = ((color_start >> 0) & 0xFF);
// 	rgb_end[0] = ((color_end >> 16) & 0xFF);
// 	rgb_end[1] = ((color_end >> 8) & 0xFF);
// 	rgb_end[2] = ((color_end >> 0) & 0xFF);
// 	rgb_start[0] = (rgb_end[0] - rgb_start[0]) * fract + rgb_start[0];
// 	rgb_start[1] = (rgb_end[1] - rgb_start[1]) * fract + rgb_start[1];
// 	rgb_start[2] = (rgb_end[2] - rgb_start[2]) * fract + rgb_start[2];
// 	return (0xFF << 24 | rgb_start[0] << 16 | rgb_start[1] << 8 | rgb_start[2]);
// }

// int	get_color_percent(int fractol_color, double percent)
// {
// 	int		rgb[3];
// 	int		argb[3];
// 	double	percentage;

// 	rgb[0] = (fractol_color >> 16) & 0xFF;
// 	rgb[1] = (fractol_color >> 8) & 0xFF;
// 	rgb[2] = (fractol_color >> 0) & 0xFF;
// 	percentage = (percent / 100) * 256;
// 	argb[0] = (rgb[0] + percentage) - 256;
// 	argb[1] = (rgb[1] + percentage) - 256;
// 	argb[2] = (rgb[2] + percentage) - 256;
// 	return (0xFF << 24 | argb[0] << 16 | argb[1] << 8 | argb[2]);
// }

// void	fill_color_stripe(t_fractol *fractol, int color, int stripe)
// {
// 	int	col;

// 	col = 0;
// 	while (col < MAX_ITERATIONS)
// 	{
// 		fractol->palette[col] = color;
// 		col += stripe;
// 	}
// }

// fractol_striped ------------------------------------------------------------/

// static void	set_color_zebra(t_fractol *fractol, int color)
// {
// 	int	color_2;

// 	color_2 = get_color_percent(color, 50);
// 	fill_color_stripe(fractol, color, 1);
// 	fill_color_stripe(fractol, color_2, 2);
// 	fractol->palette[MAX_ITERATIONS - 1] = 0;
// }

// static void	set_color_triad(t_fractol *fractol, int color)
// {
// 	int		triad[2];

// 	triad[0] = get_color_percent(color, 33);
// 	triad[1] = get_color_percent(color, 66);
// 	fill_color_stripe(fractol, color, 1);
// 	fill_color_stripe(fractol, triad[0], 2);
// 	fill_color_stripe(fractol, triad[1], 3);
// 	fractol->palette[MAX_ITERATIONS - 1] = 0;
// }

// static void	set_color_tetra(t_fractol *fractol, int color)
// {
// 	int	tetra[3];

// 	tetra[0] = get_color_percent(color, 25);
// 	tetra[1] = get_color_percent(color, 50);
// 	tetra[2] = get_color_percent(color, 75);
// 	fill_color_stripe(fractol, color, 1);
// 	fill_color_stripe(fractol, tetra[0], 2);
// 	fill_color_stripe(fractol, tetra[1], 3);
// 	fill_color_stripe(fractol, tetra[2], 4);
// 	fractol->palette[MAX_ITERATIONS - 1] = 0;
// }

// void	set_color_contrasted(t_fractol *f, int color)
// {
// 	int	i;
// 	int	r;
// 	int	g;
// 	int	b;

// 	r = (color >> 16) & 0xFF;
// 	g = (color >> 8) & 0xFF;
// 	b = (color >> 0) & 0xFF;
// 	i = -1;
// 	while (++i < MAX_ITERATIONS)
// 	{
// 		f->palette[i] = 0;
// 		if (r != 0xFF)
// 			r += i % 0xFF;
// 		if (g != 0xFF)
// 			g += i % 0xFF;
// 		if (b != 0xFF)
// 			b += i % 0xFF;
// 		f->palette[i] = 0xFF << 24 | r << 16 | g << 8 | b;
// 	}
// 	f->palette[MAX_ITERATIONS - 1] = 0;
// }

// void	set_color_opposites(t_fractol *f, int color)
// {
// 	int	i;
// 	int	r;
// 	int	g;
// 	int	b;

// 	r = (color >> 16) & 0xFF;
// 	g = (color >> 8) & 0xFF;
// 	b = (color >> 0) & 0xFF;
// 	i = -1;
// 	while (++i < MAX_ITERATIONS)
// 	{
// 		f->palette[i] = 0;
// 		r += i % 0xFF;
// 		g += i % 0xFF;
// 		b += i % 0xFF;
// 		f->palette[i] = 0xFF << 24 | r << 16 | g << 8 | b;
// 	}
// 	f->palette[MAX_ITERATIONS - 1] = 0;
// }

// void	set_color_graphic(t_fractol *f, int color)
// {
// 	int	i;
// 	int	rgb[3];

// 	rgb[0] = (color >> 16) & 0xFF;
// 	rgb[1] = (color >> 8) & 0xFF;
// 	rgb[2] = (color >> 0) & 0xFF;
// 	i = -1;
// 	while (rgb[0] < 0x33 || rgb[1] < 0x33 || rgb[2] < 0x33)
// 	{
// 		if (rgb[0] != 0xFF)
// 			rgb[0]++;
// 		if (rgb[1] != 0xFF)
// 			rgb[1]++;
// 		if (rgb[2] != 0xFF)
// 			rgb[2]++;
// 	}
// 	while (++i < MAX_ITERATIONS)
// 	{
// 		f->palette[i] = 0;
// 		rgb[0] -= i % 0xFF;
// 		rgb[1] -= i % 0xFF;
// 		rgb[2] -= i % 0xFF;
// 		f->palette[i] = 0xFF << 24 | rgb[0] << 16 | rgb[1] << 8 | rgb[2];
// 	}
// 	f->palette[MAX_ITERATIONS - 1] = 0;
// }

// static void	color_shift_special(t_fractol *f)
// {
// 	int	alt_color;

// 	if (f->color == 0xFFFFFF)
// 		alt_color = 0xCCCCCC;
// 	else
// 		alt_color = f->color;
// 	if (f->color_pattern == 5)
// 		set_color_contrasted(f, alt_color);
// 	else if (f->color_pattern == 6)
// 		set_color_opposites(f, f->color);
// 	else if (f->color_pattern == 7)
// 		set_color_graphic(f, f->color);
// 	else if (f->color_pattern == 8)
// 		fractol_colorful(f, (int [8]){0xFF0000, 0xFF7F00, 0xFFFF00,
// 			0x00FF00, 0x0000FF, 0x4B0082, 0x9400D3, 0xFFFFFF}, 8);
// }

// void	fractol_striped(t_fractol *fractol)
// {
// 	if (fractol->color_pattern == 2)
// 		set_color_zebra(fractol, fractol->color);
// 	else if (fractol->color_pattern == 3)
// 		set_color_triad(fractol, fractol->color);
// 	else if (fractol->color_pattern == 4)
// 		set_color_tetra(fractol, fractol->color);
// 	else
// 		color_shift_special(fractol);
// }

// fractol_color_shift --------------------------------------------------------/

static	void fractol_image(t_fractol *fractol)
{
	// fractol->palette = ft_calloc((MAX_ITERATIONS + 1), sizeof(int));
	// if (!(fractol->palette))
	// 	fractol_exit(fractol, msg("PALETTE ALLOCATION ERROR", ERROR));
	fractol->img_ptr = mlx_new_image(fractol->mlx_ptr, RES, RES);
	if (!(fractol->img_ptr))
		fractol_exit(fractol, msg("IMAGE CREATION ERROR", ERROR));
	fractol->pixels = mlx_get_data_addr(fractol->img_ptr,
			&fractol->bits_per_pixel, &fractol->size_line, &fractol->n);
}

// static void	fractol_image_refresh(t_fractol *fractol)
// {
// 	if (fractol->mlx_ptr && fractol->img_ptr)
// 		mlx_destroy_image(fractol->mlx_ptr, fractol->img_ptr);
// 	if (fractol->palette)
// 		free(fractol->palette);
// 	if (fractol->pixels)
// 		fractol->pixels = NULL;
// 	fractol_image(fractol);
// }

// static void	fractol_monotone(t_fractol *fractol, int color)
// {
// 	int		i;
// 	int		j;
// 	double	fract;
// 	int		color_start;
// 	int		color_end;

// 	color_start = 0x000000;
// 	color_end = color;
// 	i = 0;
// 	while (i < MAX_ITERATIONS)
// 	{
// 		j = 0;
// 		while (j < MAX_ITERATIONS / 2)
// 		{
// 			fract = (double)j /(MAX_ITERATIONS / 2);
// 			fractol->palette[i + j] = interpolation(color_start, color_end, fract);
// 			j++;
// 		}
// 		color_start = color_end;
// 		color_end = 0xFFFFFF;
// 		i += j;
// 	}
// 	fractol->palette[MAX_ITERATIONS - 1] = 0;
// }

// void	fractol_colorful(t_fractol *fractol, int colors[4], int num)
// {
// 	int		i;
// 	int		j;
// 	int		r;
// 	double	fract;

// 	i = 0;
// 	r = 0;
// 	while (i < MAX_ITERATIONS)
// 	{
// 		j = 0;
// 		while ((i + j) < MAX_ITERATIONS && j < (MAX_ITERATIONS / (num - 1)))
// 		{
// 			fract = (double)j / (MAX_ITERATIONS / (num - 1));
// 			fractol->palette[i + j] = interpolation(colors[r], colors[r + 1], fract);
// 			j++;
// 		}
// 		r++;
// 		i += j;
// 	}
// 	fractol->palette[MAX_ITERATIONS - 1] = 0;
// }

// void	fractol_color_shift(t_fractol *fractol)
// {
// 	int	color;

// 	fractol->color_pattern = (fractol->color_pattern + 1) % 9;
// 	fractol_image_refresh(fractol);
// 	if (fractol->color == 0x000000)
// 		fractol->color = 0xFFFFFF;
// 	else
// 		color = fractol->color;
// 	if (fractol->color_pattern == 0)
// 		fractol_monotone(fractol, color);
// 	else if (fractol->color_pattern == 1)
// 		fractol_colorful(fractol, (int [4]){0x000000, color,
// 			get_color_percent(fractol->color, 50), 0xFFFFFF}, 4);
// 	else
// 		fractol_striped(fractol);
// }

// fractol_initialization -----------------------------------------------------/

void	window_position(t_fractol *fractol)
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
	// fractol_color_shift(fractol);
}

// fractol_render -------------------------------------------------------------/

static int	fractol_mandelbrot(double real_cord, double i_cord)
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
		if (((real_z * real_z) + (i_z + i_z)) > 4.0)
			return (iteration_num);
		iteration_num++;
	}
	return (iteration_num);
}

static int	fractol_julia(t_fractol *fractol, double real_z, double i_z)
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

static int	calculate_fractal(t_fractol *fractol, double real_p, double i_p)
{
	int	iteration_num;

	if (fractol->set == MANDELBROT)
		iteration_num = fractol_mandelbrot(real_p, i_p);
	else if (fractol->set == JULIA)
		iteration_num = fractol_julia(fractol, real_p, i_p);
	return (iteration_num);
}
int	get_color(int color, t_fractol *fractal)
{
	return (color * fractal->color2);
}

void	put_color(int x, int y,t_fractol *fractal, int new_color)
{
	int offset;

	offset = (y * fractal->size_line) + (x * (fractal->bits_per_pixel / 8));
	*(unsigned int *)(fractal->pixels + offset) = new_color;
}

static void	fractol_pixel_color(t_fractol *fractol, int x, int y, int color)
{
	// fractol->pixels[x * 4 + y * RES * 4] = color;
	// fractol->pixels[x * 4 + y * RES * 4 + 1] = color >> 8;
	// fractol->pixels[x * 4 + y * RES * 4 + 2] = color >> 16;
	// fractol->pixels[x * 4 + y * RES * 4 + 3] = color >> 24;
	int new_color;

	new_color = get_color(color, fractol);
	put_color(x, y, fractol, new_color);
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
			if ((iteration_num == MAX_ITERATIONS) || (r_p * r_p) + (i_p * i_p) >= 4)
				put_color(x, y, f, 0x000000);
			else 
				fractol_pixel_color(f, x, y, iteration_num);
		}
	}
	mlx_put_image_to_window(f->mlx_ptr, f->mlx_win, f->img_ptr, 0, 0);
}

// fractol_args_parcing -------------------------------------------------------/

static void	atof_sign(char *str, int *col, int *sign)
{
	*col = 0;
	*sign = 1;
	while (str[*col] >= '\t' && str[*col] <= '\r' || str[*col] == ' ')
		(*col)++;
	if (str[*col] == '+')
		(*col)++;
	else if (str[*col] == '-')
	{
		*sign = -1;
		(*col)++;
	}
}

static double	fractol_atof(t_fractol *fractol, char *str)
{
	int		col;
	int		sign;
	double	res;
	double	fraction;

	atof_sign(str, &col, &sign);
	res = 0;
	while (str[col] >= '0' && str[col] <= '9')
	{
		res = res * 10 + (str[col] - '0');
		col++;
	}
	if ((str[col - 1] < '0' || str[col - 1] > '9') || str[col] != '.')
		fractol_manual_exit(fractol);
	col++;
	fraction = 0.1;
	while (str[col] >= '0' && str[col] <= '9')
	{
		res += (str[col] - '0') * fraction;
		fraction *= 0.1;
		col++;
	}
	if (str[col] != '\0')
		fractol_manual_exit(fractol);
	return (res * sign);
}

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

// fractol_hook ---------------------------------------------------------------/

static void	fractol_zoom(t_fractol *f, double zoom)
{
	double	real_center;
	double	i_center;

	real_center = f->real_min - f->real_max;
	i_center = f->i_max - f->i_min;
	f->real_max = f->real_max + (real_center - zoom * real_center) / 2;
	f->real_min = f->real_max + zoom * real_center;
	f->i_min = f->i_min + (i_center - zoom * i_center) / 2;
	f->i_max = f->i_min + zoom * i_center;
}

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

int	fractol_key_hook(int keycode, t_fractol *mlx)
{
	if (keycode == KEY_ESC)
	{
		fractol_close(mlx);
		return (0);
	}
	else if (keycode == KEY_PLUS)
		fractol_zoom(mlx, 0.5);
	else if (keycode == KEY_MINUS)
		fractol_zoom(mlx, 2);
	else if (keycode == KEY_UP)
		fractol_move(mlx, 0.2, 'U');
	else if (keycode == KEY_DOWN)
		fractol_move(mlx, 0.2, 'D');
	else if (keycode == KEY_LEFT)
		fractol_move(mlx, 0.2, 'L');
	else if (keycode == KEY_RIGHT)
		fractol_move(mlx, 0.2, 'R');
	else if (keycode == KEY_SPACE)
	{
		if (mlx->color2 == 0x020a13)
			mlx->color2 = 0x000500;
		else if (mlx->color2 == 0x000500)
			mlx->color2 = 0x080808;
		else if (mlx->color2 == 0x080808)
			mlx->color2 = 0x080000;
		else if (mlx->color2 == 0x080000)
			mlx->color2 = 0x020a13;
	}
	// else if (keycode == KEY_SPACE)
	// 	fractol_color_shift(mlx);
	else
		return (1);
	fractol_render(mlx);
	return (0);
}

int	fractol_mouse_hook(int keycode, int x, int y, t_fractol *mlx)
{
	if (keycode == MOUSE_SCROLL_UP)
	{
		fractol_zoom(mlx, 0.5);
		x -= RES / 2;
		y -= RES / 2;
		if (x < 0)
			fractol_move(mlx, (double)x * -1 / RES, 'L');
		else if (x > 0)
			fractol_move(mlx, (double)x / RES, 'R');
		if (y < 0)
			fractol_move(mlx, (double)y * -1 / RES, 'U');
		else if (y > 0)
			fractol_move (mlx, (double)y / RES, 'D');
	}
	else if (keycode == MOUSE_SCROLL_DOWN)
		fractol_zoom(mlx, 2);
	else
		return (0);
	fractol_render(mlx);
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
	fractol->color2 = 0x020a13;
	fractol->color = 0xFFFFFF;
	fractol->color_pattern = -1;
	fractol->palette = NULL;
}

void f(void)
{
	system("leaks a.out");
}

int	main(int ac, char **av)
{
	atexit(f);
	t_fractol	fractol;

	if (ac == 1)
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
