/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:53:19 by jihoh             #+#    #+#             */
/*   Updated: 2022/01/20 19:04:24 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fractol.h"

void	init_vars(t_frctl *frctl, t_img *img)
{
	frctl->x = -1;
	frctl->y = -1;
	frctl->mlx = mlx_init(); // mlx
	frctl->win = mlx_new_window(frctl->mlx, WIN_W, WIN_H, "mlx 42");
	frctl->xmin = -1.5;
	frctl->xmax = 0.6;
	frctl->ymin = -1.2;
	frctl->ymax = 1.2;
	frctl->itermax = 42;
	img->img = mlx_new_image(frctl->mlx, WIN_W, WIN_H);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_length,
								&img->endian);
}

void	put_pix_on_img(t_img *img, int x, int y, t_color *clr)
{
	int	pos;

	pos = x * img->bpp / 8 + y * img->line_length;
	img->addr[pos] = clr->b;
	img->addr[pos + 1] = clr->g;
	img->addr[pos + 2] = clr->r;
}

void	mandelbrot(t_frctl *frctl, t_img *img, t_cmplx *c, t_cmplx *z)
{
	int		i;
	t_cmplx	*tmp;
	t_color	clr;

	c->r = frctl->x / (WIN_W / (frctl->xmax - frctl->xmin)) + frctl->xmin;
	c->i = frctl->y / (WIN_H / (frctl->ymax - frctl->ymin)) + frctl->ymin;
	z->r = 0;
	z->i = 0;
	i = -1;
	while (++i < frctl->itermax)
	{
		tmp = z;
		z->r = tmp->r * tmp->r - tmp->i * tmp->i + c->r;
		z->i = 2 * tmp->r * z->i + c->i;
		if ((z->r * z->r + z->i * z->i) > 4.0)
			break ;
	}
	if (i == frctl->itermax)
	{
		clr.r = 0;
		clr.g = 0;
		clr. b = 0;
	}
	else
	{
		clr.r = (i * 7) % 255;
		clr.g = (142 + (i * 2)) % 255;
		clr.b = (255 - (i * 8)) % 255;
	}
	put_pix_on_img(img, frctl->x, frctl->y, &clr);		
}

int	main(void)
{
	t_frctl	frctl;
	t_img	img;
	t_cmplx c;
	t_cmplx	z;
	int		cnt_w;
	int		cnt_h;
	int		i;
	
	init_vars(&frctl, &img);
	mlx_put_image_to_window(frctl.mlx, frctl.win, img.img, 0, 0);
	frctl.y = -1;
	while (++frctl.y< WIN_H)
	{
		frctl.x = -1;
		while (++frctl.x < WIN_W)
		{
			mandelbrot(&frctl, &img, &c, &z);
		}
	}
	mlx_loop(frctl.mlx);
	return (0);
}
