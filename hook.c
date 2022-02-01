/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 19:09:52 by jihoh             #+#    #+#             */
/*   Updated: 2022/02/02 03:45:46 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
	frctl->offx += before.r - after.r;
	frctl->offy += before.i - after.i;
	draw_fractol(frctl, &frctl->data);
	return (0);
}

int	key_hook(int keycode, t_frctl *frctl)
{
	double	offset;

	offset = 0.2f * frctl->zoom;
	if (keycode == KEY_ESC)
		exit(0);
	else if (keycode == UP_ARROW)
		frctl->offy -= offset;
	else if (keycode == DOWN_ARROW)
		frctl->offy += offset;
	else if (keycode == LEFT_ARROW)
		frctl->offx -= offset;
	else if (keycode == RIGHT_ARROW)
		frctl->offx += offset;
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
