/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:53:19 by jihoh             #+#    #+#             */
/*   Updated: 2022/01/30 19:11:42 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
	frctl->itermax = 42;
}

int	main(int argc, char **argv)
{
	t_frctl	frctl;

	init_vars(&frctl);
	mlx_hook(frctl.win, ON_KEYDOWN, 1L << 0, key_press, &frctl);
	mlx_hook(frctl.win, ON_MOUSEDOWN, 1L << 2, mouse_hook, &frctl);
	draw_fractol(&frctl, &frctl.data);
	mlx_loop(frctl.mlx);
	return (0);
}
