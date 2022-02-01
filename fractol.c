/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 19:08:48 by jihoh             #+#    #+#             */
/*   Updated: 2022/02/02 00:21:38 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	screen_to_world(t_point *point, t_cmplx *cmplx, t_frctl *fr)
{
	double	xscale;
	double	yscale;

	xscale = (fr->xmax - fr->xmin) / WIN_W;
	yscale = (fr->ymax - fr->ymin) / WIN_H;
	cmplx->r = (double)point->x * xscale * fr->zoom + fr->xmin + fr->offx;
	cmplx->i = (double)point->y * yscale * fr->zoom + fr->ymin + fr->offy;
}

void	spider(t_frctl *frctl, t_data *data, t_point point)
{
	t_cmplx	c;
	t_cmplx	z;
	t_cmplx	tmp;
	int		iter;

	screen_to_world(&point, &c, frctl);
	z.r = 0;
	z.i = 0;
	iter = -1;
	frctl->itermax = 42;
	while (++iter < frctl->itermax)
	{
		tmp = z;
		z.r = tmp.r * tmp.r - tmp.i * tmp.i + c.r;
		z.i = 2 * tmp.r * tmp.i + c.i;
		c.r = c.r / 2 + z.r;
		c.i = c.i / 2 + z.i;
		if (z.r * z.r + z.i * z.i > 4.0)
			break ;
	}
	put_color(data, point, get_color(iter, frctl, &frctl->clrset));
}

void	julia(t_frctl *frctl, t_data *data, t_point point)
{
	t_cmplx	c;
	t_cmplx	z;
	t_cmplx	tmp;
	int		iter;

	screen_to_world(&point, &z, frctl);
	c.r = 0.285;
	c.i = 0.01;
	iter = -1;
	frctl->itermax = 128;
	while (++iter < frctl->itermax)
	{
		tmp = z;
		z.r = tmp.r * tmp.r - tmp.i * tmp.i + c.r;
		z.i = 2 * tmp.r * tmp.i + c.i;
		if (z.r * z.r + z.i * z.i > 4.0)
			break ;
	}
	put_color(data, point, get_color(iter, frctl, &frctl->clrset));
}

void	mandelbrot(t_frctl *frctl, t_data *data, t_point point)
{
	t_cmplx	c;
	t_cmplx	z;
	t_cmplx	tmp;
	int		iter;

	screen_to_world(&point, &c, frctl);
	z.r = 0;
	z.i = 0;
	iter = -1;
	frctl->itermax = 42;
	while (++iter < frctl->itermax)
	{
		tmp = z;
		z.r = tmp.r * tmp.r - tmp.i * tmp.i + c.r;
		z.i = 2 * tmp.r * tmp.i + c.i;
		if (z.r * z.r + z.i * z.i > 4.0)
			break ;
	}
	put_color(data, point, get_color(iter, frctl, &frctl->clrset));
}
