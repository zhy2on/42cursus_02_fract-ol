/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_frctl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:53:19 by jihoh             #+#    #+#             */
/*   Updated: 2022/01/30 18:09:08 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_frctl.h"
#include <stdio.h>

int	mousewheel_hook(int button, int x, int y, t_frctl *frctl)
{
	double	z;
	t_cmplx	before;
	t_cmplx	after;
	t_point	point;

	z = 1.05f;
	point.x = x;
	point.y = y;
	if (button == ON_MOUSEDOWN)
	{
		printf("x y: %d %d\n", x, y);
		screen_to_world(&point, &before, frctl);
		frctl->zoom *= z;
		screen_to_world(&point, &after, frctl);
		frctl->offx += before.r - after.r;
		frctl->offy += before.i - after.i;
		printf("before after: %f %f %f %f\n", before.r, before.i, after.r, after.i);
		draw_fractol(frctl, &frctl->data);
	}
	else if (button == ON_MOUSEUP)
	{
		printf("x y: %d %d\n", x, y);
		screen_to_world(&point, &before, frctl);
		z = 1.0 / z;
		frctl->zoom *= z;
		screen_to_world(&point, &after, frctl);
		frctl->offx += before.r - after.r;
		frctl->offy += before.i - after.i;
		printf("before after: %f %f %f %f\n", before.r, before.i, after.r, after.i);
		/*
		z = 1.0 / z;
		screen_to_world(&point, &before, frctl);
		frctl->xmin += (before.r - frctl->xmin) * (1 - z);
		frctl->xmax -= (frctl->xmax - before.r) * (1 - z);
		frctl->ymin += (before.i - frctl->ymin) * (1 - z);
		frctl->ymax -= (frctl->ymax - before.i) * (1 - z);
		screen_to_world(&point, &after, frctl);
		printf("before after: %f %f %f %f\n", before.r, before.i, after.r, after.i);
		draw_fractol(frctl, &frctl->data);
		*/
	}
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

int	key_press(int keycode, t_frctl *frctl)
{
	double	offset;

	offset = 0.2f * frctl->zoom;
	if (keycode == KEY_ESC)
		exit(0);
	else if (keycode == UP_ARROW)
	{
		frctl->offy -= offset;
		draw_fractol(frctl, &frctl->data);
	}
	else if (keycode == DOWN_ARROW)
	{
		frctl->offy += offset;
		draw_fractol(frctl, &frctl->data);
	}
	else if (keycode == LEFT_ARROW)
	{
		frctl->offx -= offset;
		draw_fractol(frctl, &frctl->data);
	}
	else if (keycode == RIGHT_ARROW)
	{
		frctl->offx += offset;
		draw_fractol(frctl, &frctl->data);
	}
	return (0);
}

void	screen_to_world(t_point *point, t_cmplx *cmplx, t_frctl *fr)
{
	double	xscale;
	double	yscale;

	xscale = (double)(fr->xmax - fr->xmin) / WIN_W;
	yscale = (double)(fr->ymax - fr->ymin) / WIN_H;
	cmplx->r = point->x * xscale + fr->xmin + fr->offx;
	cmplx->i = point->y * yscale + fr->ymin + fr->offy;
}

void	mandelbrot(t_frctl *frctl, t_data *data, t_point point)
{
	t_clr	clr;
	t_cmplx	c;
	t_cmplx	z;
	t_cmplx	tmp;
	int		iter;

	screen_to_world(&point, &c, frctl);
	z.r = 0;
	z.i = 0;
	iter = -1;
	while (++iter < frctl->itermax)
	{
		tmp = z;
		z.r = tmp.r * tmp.r - tmp.i * tmp.i + c.r;
		z.i = 2 * tmp.r * tmp.i + c.i;
		if (z.r * z.r + z.i * z.i > 4.0)
			break ;
	}
	clr.r = (frctl->itermax - iter) % 255;
	clr.g = (frctl->itermax - iter) % 255 + 10;
	clr.b = (frctl->itermax - iter) % 255 + 20;
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
	frctl->offx = 0;
	frctl->offy = 0;
	frctl->zoom = 1;
	frctl->itermax = 128;
}

int	main(void)
{
	t_frctl	frctl;

	init_vars(&frctl);
	mlx_hook(frctl.win, ON_KEYDOWN, 1L << 0, key_press, &frctl);
	mlx_hook(frctl.win, ON_MOUSEDOWN, 1L << 2, mousewheel_hook, &frctl);
	draw_fractol(&frctl, &frctl.data);
	mlx_loop(frctl.mlx);
	return (0);
}
