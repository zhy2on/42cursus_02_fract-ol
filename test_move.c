/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:53:19 by jihoh             #+#    #+#             */
/*   Updated: 2022/01/26 15:45:28 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

int	mousemove_hook(int x, int y, t_frctl *frctl)
{
	t_cmplx	cmplx;

	if (frctl->mouse_pressed)
	{
		printf("mouse move %d %d\n", x, y);
	}
	return (0);
}

int	mousepress_hook(int button, int x, int y, t_frctl *frctl)
{
	if (button == LEFT_CLICK)
	{
		frctl->mouse_pressed = 1;
		printf("mouse pressed button %d x,y %d %d\n", button, x, y);
	}
	else
		mousewheel_hook(button, x, y, frctl);
	return (0);
}

int	mouserelease_hook(int button, int x, int y, t_frctl *frctl)
{
	printf("mouse released button %d x,y %d %d\n", button, x, y);
	frctl->mouse_pressed = 0;
	return (0);
}

void	zoom(t_frctl *frctl, t_data *data, int x, int y)
{
	t_cmplx	cmplx;

	cmplx.cr = map(x, 0, WIN_W, frctl->xmin, frctl->xmax);
	cmplx.ci = map(y, 0, WIN_H, frctl->ymin, frctl->ymax);
	cmplx.tmp = frctl->xmax - frctl->xmin;
	frctl->xmin = cmplx.cr - (cmplx.tmp / frctl->zoom);
	frctl->xmax = cmplx.cr + (cmplx.tmp / frctl->zoom);
	cmplx.tmp = frctl->ymax - frctl->ymin;
	frctl->ymin = cmplx.ci - (cmplx.tmp / frctl->zoom);
	frctl->ymax = cmplx.ci + (cmplx.tmp / frctl->zoom);
}

int	mousewheel_hook(int button, int x, int y, t_frctl *frctl)
{
	t_point	point;
	t_cmplx	cmplx;

	return (0);
}

int	key_press(int keycode, t_frctl *frctl)
{
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_A)
		printf("Hello from key_press!\n");
	return (0);
}

void	put_color(t_data *data, t_point point, t_clr clr)
{
	int	pos;

	pos = point.x * data->bpp / 8 + point.y * data->bpl;
	data->buff[pos] = clr.b;
	data->buff[pos + 1] = clr.g;
	data->buff[pos + 2] = clr.r;
}

double	map(double n, double in_min, double in_max, double out_min, double out_max)
{
	return ((n - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}

void	mandelbrot(t_frctl *frctl, t_data *data, t_point point)
{
	t_clr	clr;
	t_cmplx	cmplx;
	int		iter;
	int		bright;

	cmplx.cr = map(point.x, 0, WIN_W, frctl->xmin, frctl->xmax);
	cmplx.ci = map(point.y, 0, WIN_H, frctl->ymin, frctl->ymax);
	cmplx.zr = 0;
	cmplx.zi = 0;
	iter = -1;
	while (++iter < frctl->itermax)
	{
		cmplx.tmp = cmplx.zr;
		cmplx.tmp = cmplx.zr * cmplx.zr - cmplx.zi * cmplx.zi + cmplx.cr;
		cmplx.zi = 2 * cmplx.zr * cmplx.zi + cmplx.ci;
		cmplx.zr = cmplx.tmp;
		if (cmplx.zr * cmplx.zr + cmplx.zi * cmplx.zi > 4)
			break ;
	}
	clr.r = 1.0 * (frctl->itermax - iter) / frctl->itermax * 0xff;
	clr.g = clr.r;
	clr.b = clr.r;
	put_color(data, point, clr);
}

void	draw_fractol(t_frctl *frctl, t_data *data)
{
	t_point	point;

	point.y = -1;
	while (++point.y < WIN_H)
	{
		point.x = -1;
		while (++point.x < WIN_W)
			mandelbrot(frctl, data, point);
	}
	mlx_put_image_to_window(frctl->mlx, frctl->win, data->img, 0, 0);
}

void	draw_rectangle(t_frctl *frctl, t_data *data)
{
	t_point	point;
	t_clr	clr;

	clr.r = 255;
	clr.g = 255;
	clr.b = 255;
	point.y = -1;
	while (++point.y < 100)
	{
		point.x = -1;
		while (++point.x < 100)
		{
			put_color(data, point, clr);
		}
	}
	mlx_put_image_to_window(frctl->mlx, frctl->win, data->img, 0, 0);
}

void	init_vars(t_frctl *frctl)
{
	frctl->mlx = mlx_init();
	frctl->win = mlx_new_window(frctl->mlx, WIN_W, WIN_H, "mlx 42");
	frctl->data.img = mlx_new_image(frctl->mlx, WIN_W, WIN_H);
	frctl->data.buff = mlx_get_data_addr(frctl->data.img, &frctl->data.bpp,
			&frctl->data.bpl, &frctl->data.endian);
	frctl->xmin = -2.5;
	frctl->xmax = 1;
	frctl->ymin = -1;
	frctl->ymax = 1;
	frctl->last_point.x = 0;
	frctl->last_point.y = 0;
	frctl->itermax = 128;
	frctl->mouse_pressed = 0;
}

int	main(void)
{
	t_frctl	frctl;

	init_vars(&frctl);
	mlx_hook(frctl.win, ON_KEYDOWN, 1L << 0, key_press, &frctl);
	mlx_hook(frctl.win, ON_MOUSEDOWN, 1L << 8, mousepress_hook, &frctl);
	mlx_hook(frctl.win, ON_MOUSEUP, 1L << 9, mouserelease_hook, &frctl);
	mlx_hook(frctl.win, ON_MOUSEMOVE, 1L << 13, mousemove_hook, &frctl);
	draw_rectangle(&frctl, &frctl.data);
	mlx_loop(frctl.mlx);
	return (0);
}
