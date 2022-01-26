/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:53:19 by jihoh             #+#    #+#             */
/*   Updated: 2022/01/26 17:42:47 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void	clear_image(t_frctl *frctl)
{
	t_point	point;
	t_clr	clr;

	clr.r = 0;
	clr.g = 0;
	clr.b = 0;
	point.y = -1;
	while (++point.y < WIN_H)
	{
		point.x = -1;
		while (++point.x < WIN_W)
		{
			put_color(&frctl->data, point, clr);
		}
	}
}

int	mousemove_hook(int x, int y, t_frctl *frctl)
{
	t_cmplx	cmplx;

	if (frctl->mouse_pressed)
	{
		frctl->offx -= x - frctl->lstx;
		frctl->offy -= y - frctl->lsty;
		frctl->lstx = x;
		frctl->lsty = y;
		printf("clear window\n");
		clear_image(frctl);
		draw_rectangle(frctl, &frctl->data);
		printf("mouse move %d %d\n", x, y);
	}
	return (0);
}

int	mousepress_hook(int button, int x, int y, t_frctl *frctl)
{
	if (button == LEFT_CLICK)
	{
		frctl->mouse_pressed = 1;
		frctl->lstx = x;
		frctl->lsty = y;
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

	if (point.x < 0 || point.y < 0 || point.x > WIN_W - 1|| point.y > WIN_H - 1)
		return ;
	pos = point.x * data->bpp / 8 + point.y * data->bpl;
	data->buff[pos] = clr.b;
	data->buff[pos + 1] = clr.g;
	data->buff[pos + 2] = clr.r;
}

double	map(double n, double in_min, double in_max, double out_min, double out_max)
{
	return ((n - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}

void	draw_rectangle(t_frctl *frctl, t_data *data)
{
	t_point	point;
	t_clr	clr;

	clr.r = 255;
	clr.g = 255;
	clr.b = 255;
	point.y = -1 - frctl->offy;
	while (++point.y < 100 - frctl->offy)
	{
		point.x = -1 - frctl->offx;
		while (++point.x < 100 - frctl->offx)
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
	frctl->offx = -WIN_W / 2;
	frctl->offy = -WIN_H / 2;
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
