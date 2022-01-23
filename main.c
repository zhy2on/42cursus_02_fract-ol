/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:53:19 by jihoh             #+#    #+#             */
/*   Updated: 2022/01/23 16:29:28 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	key_press(int keycode, t_frctl *vars)
{
	if (keycode == KEY_ESC)
		exit(0);
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

void	mandelbrot(t_frctl *frctl, t_data *data, t_point point)
{
	t_clr	clr;
	t_cmplx	cmplx;
	int		iter;

	cmplx.cr = frctl->rmin + (frctl->rmax - frctl->rmin) * point.x / WIN_W;
	cmplx.ci = frctl->imin + (frctl->imax - frctl->imin) * point.y / WIN_H;
	cmplx.zr = 0;
	cmplx.zi = 0;
	iter = -1;
	while (++iter < frctl->itermax)
	{
		cmplx.tmpr = cmplx.zr;
		cmplx.tmpr = cmplx.zr * cmplx.zr - cmplx.zi * cmplx.zi + cmplx.cr;
		cmplx.zi = 2 * cmplx.zr * cmplx.zi + cmplx.ci;
		cmplx.zr = cmplx.tmpr;
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
}

void	init_vars(t_frctl *frctl, t_data *data)
{
	frctl->mlx = mlx_init();
	frctl->win = mlx_new_window(frctl->mlx, WIN_W, WIN_H, "mlx 42");
	data->img = mlx_new_image(frctl->mlx, WIN_W, WIN_H);
	data->buff = mlx_get_data_addr(data->img, &data->bpp, &data->bpl,
			&data->endian);
	frctl->rmin = -2.5;
	frctl->rmax = 1;
	frctl->imin = -1;
	frctl->imax = 1;
	frctl->itermax = 1000;
}

int	main(void)
{
	t_frctl	frctl;
	t_data	data;

	init_vars(&frctl, &data);
	draw_fractol(&frctl, &data);
	mlx_hook(frctl.win, ON_KEYDOWN, 1L << 0, key_press, &frctl);
	mlx_put_image_to_window(frctl.mlx, frctl.win, data.img, 0, 0);
	mlx_loop(frctl.mlx);
	return (0);
}
