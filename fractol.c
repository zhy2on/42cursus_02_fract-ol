/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 19:08:48 by jihoh             #+#    #+#             */
/*   Updated: 2022/01/30 19:11:05 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	screen_to_world(t_point *point, t_cmplx *cmplx, t_frctl *fr)
{
	double	xscale;
	double	yscale;

	xscale = (double)(fr->xmax - fr->xmin) / WIN_W;
	yscale = (double)(fr->ymax - fr->ymin) / WIN_H;
	cmplx->r = point->x * xscale * fr->zoom + fr->xmin + fr->offx;
	cmplx->i = point->y * yscale * fr->zoom + fr->ymin + fr->offy;
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
	clr.r = 1.0 * (frctl->itermax - iter) / frctl->itermax * 0xff;
	clr.g = clr.r;
	clr.b = clr.r;
	put_color(data, point, clr);
}