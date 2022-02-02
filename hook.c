/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 19:09:52 by jihoh             #+#    #+#             */
/*   Updated: 2022/02/03 01:19:54 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	world_to_screen(t_cmplx *cmplx, t_point *point, t_frctl *fr)
{
	double	rscale;
	double	iscale;

	rscale = (fr->rmax - fr->rmin) / WIN_W;
	iscale = (fr->imax - fr->imin) / WIN_H;
	point->x = (cmplx->r - fr->rmin) / fr->zoom / rscale - fr->offx;
	point->y = (cmplx->i - fr->imin) / fr->zoom / iscale - fr->offy;
}

int	mouse_hook(int button, int x, int y, t_frctl *frctl)
{
	t_cmplx	cmplx;
	t_point	before;
	t_point	after;
	double	zoom;

	if (y < 0)
		return (0);
	zoom = 1.1f;
	before.x = x;
	before.y = WIN_H - y - 1;
	screen_to_world(&before, &cmplx, frctl);
	if (button == SCROLL_UP)
		frctl->zoom *= 1.0 / zoom;
	else if (button == SCROLL_DOWN)
		frctl->zoom *= zoom;
	else
		return (0);
	world_to_screen(&cmplx, &after, frctl);
	frctl->offx -= before.x - after.x;
	frctl->offy -= before.y - after.y;
	draw_fractol(frctl, &frctl->data);
	return (0);
}

int	key_hook(int keycode, t_frctl *frctl)
{
	double	offset;

	offset = 0.1;
	if (keycode == KEY_ESC)
		exit(0);
	else if (keycode == UP_ARROW)
		frctl->offy -= WIN_H * offset;
	else if (keycode == DOWN_ARROW)
		frctl->offy += WIN_H * offset;
	else if (keycode == LEFT_ARROW)
		frctl->offx -= WIN_W * offset;
	else if (keycode == RIGHT_ARROW)
		frctl->offx += WIN_W * offset;
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
