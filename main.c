/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:53:19 by jihoh             #+#    #+#             */
/*   Updated: 2022/02/01 03:18:43 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

void	draw_fractol(t_frctl *frctl, t_data *data)
{
	t_point	point;

	point.y = -1;
	while (++point.y < WIN_H)
	{
		point.x = -1;
		while (++point.x < WIN_W)
		{
			if (frctl->frctl_num == 1)
				julia(frctl, data, point);
			else if (frctl->frctl_num == 2)
				mandelbrot(frctl, data, point);
			else
				spider(frctl, data, point);
		}
	}
	mlx_put_image_to_window(frctl->mlx, frctl->win, data->img, 0, 0);
}

void	init_vars_sub(t_frctl *frctl)
{
	frctl->xmin = -2.1;
	frctl->xmax = 1.9;
	frctl->ymin = -1.2;
	frctl->ymax = 1.2;
	if (frctl->frctl_num == 2)
	{
		frctl->xmin = -2.5;
		frctl->xmax = 1.0;
		frctl->ymin = -1.0;
		frctl->ymax = 1.0;
	}
	else if (frctl->frctl_num == 3)
	{
		frctl->xmin = -3.0;
		frctl->xmax = 1.0;
		frctl->ymin = -1.2;
		frctl->ymax = 1.2;
	}
	frctl->offx = 0;
	frctl->offy = 0;
	frctl->zoom = 1;
	frctl->itermax = 42;
}

void	init_vars(t_frctl *frctl, char *argv)
{
	if (ft_strncmp(argv, "julia", 5) == 0)
		frctl->frctl_num = 1;
	else if (ft_strncmp(argv, "mandelbrot", 10) == 0)
		frctl->frctl_num = 2;
	else if (ft_strncmp(argv, "spider", 6) == 0)
		frctl->frctl_num = 3;
	else
		exit(0);
	frctl->mlx = mlx_init();
	frctl->win = mlx_new_window(frctl->mlx, WIN_W, WIN_H, "jihoh's fractol");
	frctl->data.img = mlx_new_image(frctl->mlx, WIN_W, WIN_H);
	frctl->data.buff = mlx_get_data_addr(frctl->data.img, &frctl->data.bpp,
			&frctl->data.bpl, &frctl->data.endian);
	init_vars_sub(frctl);
}

int	main(int argc, char **argv)
{
	t_frctl	frctl;

	if (argc < 2)
		return (0);
	init_vars(&frctl, argv[1]);
	mlx_hook(frctl.win, ON_KEYDOWN, 1L << 0, key_press, &frctl);
	mlx_hook(frctl.win, ON_MOUSEDOWN, 1L << 2, mouse_hook, &frctl);
	draw_fractol(&frctl, &frctl.data);
	mlx_loop(frctl.mlx);
	return (0);
}
