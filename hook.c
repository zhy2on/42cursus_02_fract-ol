/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 19:09:52 by jihoh             #+#    #+#             */
/*   Updated: 2022/02/01 03:46:28 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mouse_hook(int button, int x, int y, t_frctl *frctl)
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
		screen_to_world(&point, &before, frctl);
		frctl->zoom *= z;
	}
	else if (button == ON_MOUSEUP)
	{
		screen_to_world(&point, &before, frctl);
		frctl->zoom *= 1.0 / z;
	}
	else
		return (0);
	screen_to_world(&point, &after, frctl);
	frctl->offx += before.r - after.r;
	frctl->offy -= before.i - after.i;
	draw_fractol(frctl, &frctl->data);
	return (0);
}

int	key_press(int keycode, t_frctl *frctl)
{
	double	offset;

	offset = 0.2f * frctl->zoom;
	printf("keycode: %d\n", keycode);
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
	else
		return (0);
	draw_fractol(frctl, &frctl->data);
	return (0);
}
