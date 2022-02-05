/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 19:08:48 by jihoh             #+#    #+#             */
/*   Updated: 2022/02/05 16:31:24 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	screen_to_world(t_point *point, t_cmplx *cmplx, t_frctl *fr)
{
	double	rscale;
	double	iscale;

	rscale = (fr->rmax - fr->rmin) / WIN_W;
	iscale = (fr->imax - fr->imin) / WIN_H;
	cmplx->r = (point->x + fr->offx) * rscale * fr->zoom + fr->rmin;
	cmplx->i = (point->y + fr->offy) * iscale * fr->zoom + fr->imin;
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
	if (frctl->is_use_param)
		c = frctl->julia_c;
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
	if (iter == frctl->itermax)
		iter = 0;
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

void	draw_fractol(t_frctl *frctl, t_data *data)
{
	t_point	point;

	point.y = -1;
	while (++point.y < WIN_H)
	{
		point.x = -1;
		while (++point.x < WIN_W)
		{
			if (frctl->type == 1)
				julia(frctl, data, point);
			else if (frctl->type == 2)
				mandelbrot(frctl, data, point);
			else
				spider(frctl, data, point);
		}
	}
	mlx_put_image_to_window(frctl->mlx, frctl->win, data->img, 0, 0);
}
