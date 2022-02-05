/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:53:19 by jihoh             #+#    #+#             */
/*   Updated: 2022/02/05 17:50:26 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	ft_atof(const char *str)
{
	double			sign;
	unsigned int	num;
	double			i;

	sign = 1;
	num = 0;
	i = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		num = num * 10 + (*str++ - '0');
	str++;
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str++ - '0');
		i *= 0.1;
	}
	return (sign * num * i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n && *s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
		n--;
	}
	if (n)
		return ((unsigned char)(*s1) - (unsigned char)(*s2));
	return (0);
}

void	init_viewset(t_frctl *frctl)
{
	if (frctl->type == 1)
	{
		frctl->rmin = -2.1;
		frctl->rmax = 1.9;
		frctl->imin = -1.2;
		frctl->imax = 1.2;
	}
	else if (frctl->type == 2)
	{
		frctl->rmin = -2.7;
		frctl->rmax = 1.2;
		frctl->imin = -1.1;
		frctl->imax = 1.1;
	}
	else if (frctl->type == 3)
	{
		frctl->rmin = -3.0;
		frctl->rmax = 1.0;
		frctl->imin = -1.2;
		frctl->imax = 1.2;
	}
	frctl->offx = 0;
	frctl->offy = 0;
	frctl->zoom = 1.0;
}

void	init_vars(t_frctl *frctl, char **argv)
{
	frctl->is_use_param = 0;
	if (argv[1] && ft_strncmp(argv[1], "julia", 5) == 0)
		frctl->type = 1;
	else if (argv[1] && ft_strncmp(argv[1], "mandelbrot", 10) == 0)
		frctl->type = 2;
	else if (argv[1] && ft_strncmp(argv[1], "spider", 6) == 0)
		frctl->type = 3;
	else
	{
		write(1, "Usage: ./fractol + 'julia' or 'mandelbrot' or 'spider'\n", 56);
		exit(0);
	}
	if (frctl->type == 1 && argv[2] && argv[3])
	{
		frctl->is_use_param = 1;
		frctl->julia_c.r = ft_atof(argv[2]);
		frctl->julia_c.i = ft_atof(argv[3]);
	}
	frctl->mlx = mlx_init();
	frctl->win = mlx_new_window(frctl->mlx, WIN_W, WIN_H, "jihoh's fractol");
	frctl->data.img = mlx_new_image(frctl->mlx, WIN_W, WIN_H);
	frctl->data.buff = mlx_get_data_addr(frctl->data.img, &frctl->data.bpp,
			&frctl->data.bpl, &frctl->data.endian);
	init_viewset(frctl);
	init_clrset(&frctl->clrset);
}

int	main(int argc, char **argv)
{
	t_frctl	frctl;

	init_vars(&frctl, argv);
	mlx_hook(frctl.win, ON_KEYDOWN, 1L << 0, key_hook, &frctl);
	mlx_hook(frctl.win, ON_MOUSEDOWN, 1L << 2, mouse_hook, &frctl);
	draw_fractol(&frctl, &frctl.data);
	mlx_loop(frctl.mlx);
	return (0);
}
