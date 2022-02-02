/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 19:09:52 by jihoh             #+#    #+#             */
/*   Updated: 2022/02/02 22:37:27 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	zoom_interpolation(double start, double end, double interpol)
{
	return (start + ((end - start) * interpol));
}

void	apply_zoom(t_frctl *fr, double r, double i, double zoom)
{
	double	z;

	z = 1.0 / zoom;
	fr->rmin = zoom_interpolation(r, fr->rmin, z);
	fr->rmax = zoom_interpolation(r, fr->rmax, z);
	fr->imin = zoom_interpolation(i, fr->imin, z);
	fr->imax = zoom_interpolation(i, fr->imax, z);
}

int	mouse_hook(int button, int x, int y, t_frctl *frctl)
{
	double	z;
	t_cmplx	before;
	t_cmplx	after;
	t_point	point;

	z = 1.1f;
	point.x = x;
	point.y = y;
	if (button == ON_MOUSEUP)
	{
		screen_to_world(&point, &before, frctl);
		frctl->zoom *= 0.9;
	}
	else if (button == ON_MOUSEDOWN)
	{
		screen_to_world(&point, &before, frctl);
		frctl->zoom *= 1.1;
	}
	else
		return (0);
	screen_to_world(&point, &after, frctl);
	frctl->off_r += before.r - after.r;
	frctl->off_i += before.i - after.i;
	draw_fractol(frctl, &frctl->data);
	return (0);
	/*
	t_cmplx	before;
	t_cmplx	after;
	t_point	point;

	if (x < 0 || y < 0 || x >= WIN_W || y >= WIN_H)
		return (0);
	point.x = x;
	point.y = y;
	printf("x,y: %d %d\n", x, y);
	screen_to_world(&point, &before, frctl);
	if (button == ON_MOUSEUP)
		apply_zoom(frctl, before.r, before.i, 1.1);
	else if (button == ON_MOUSEDOWN)
		apply_zoom(frctl, before.r, before.i, 1.0 / 1.1);
	else
		return (0);
	printf("position: %f %f\n", before.r, before.i);
	draw_fractol(frctl, &frctl->data);
	return (0);
	*/
}

int	key_hook(int keycode, t_frctl *frctl)
{
	double	offset;

	offset = 0.2f * frctl->zoom;
	if (keycode == KEY_ESC)
		exit(0);
	else if (keycode == UP_ARROW)
		frctl->off_i -= offset;
	else if (keycode == DOWN_ARROW)
		frctl->off_i += offset;
	else if (keycode == LEFT_ARROW)
		frctl->off_r -= offset;
	else if (keycode == RIGHT_ARROW)
		frctl->off_r += offset;
	else if (keycode == KEY_1)
		frctl->clrset.clrsize = 5;
	else if (keycode == KEY_2)
		frctl->clrset.clrsize = 6;
	else if (keycode == KEY_3)
		frctl->clrset.clrsize = 7;
	else
		return (0);
	draw_fractol(frctl, &frctl->data);
	return (0);
}
