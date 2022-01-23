/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:45:27 by jihoh             #+#    #+#             */
/*   Updated: 2022/01/23 15:20:31 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define WIN_W 500
#define WIN_H 500
#define RANGE_CHANGE(x, a, b, min, max) (((b) - (a)) * ((x) - (min)) / ((max) - (min))) + (a)

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17,
	KEY_ESC = 53,
	KEY_W = 13,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2
};

typedef struct s_clr
{
	uint8_t	r; //unsigned_char == uint8_t
	uint8_t	g;
	uint8_t	b;
}				t_clr;

typedef struct	s_cmplx
{
	double		r; //real
	double		i; //img
}				t_cmplx;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

int	key_hook(int keycode, t_vars *vars)
{
	printf("Hello from key_hook!\n");
	return (0);
}

int	mouse_hook(int keycode, t_vars *vars)
{
	printf("Hello from mouse_hook!\n");
	return (0);
}

int	key_press(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

int main(void)
{
	void *image;

	int pixel_bits;
	int line_bytes;
	int endian;
	
	int count_w;
	int count_h;
	t_vars	vars;
	t_cmplx c;
	t_cmplx z;

	int	iter;
	t_cmplx	tmp;

	// for zoom
	double min_re = -2.5;
	double max_re = 1;
	double min_im = -1;
	double max_im = 1;
	const int	max_iter = 1000;
	t_clr	clr;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIN_W, WIN_H, "mlx 42");
	image = mlx_new_image(vars.mlx, WIN_W, WIN_H);

	char *buffer = (char *)mlx_get_data_addr(image, &pixel_bits, &line_bytes, &endian);

	count_h = -1;
	while (++count_h < WIN_H)
	{
		count_w = -1;
		while (++count_w < WIN_W)
		{
			c.r = min_re + (max_re - min_re) * count_w / WIN_W;
			c.i = min_im + (max_im - min_im) * count_h / WIN_H;
			z.r = 0;
			z.i = 0;
			
			iter = 1;
			while (++iter < max_iter)
			{
				tmp = z;
				z.r = tmp.r * tmp.r - tmp.i * tmp.i + c.r;
				z.i = 2 * tmp.r * tmp.i + c.i;
				if (z.r * z.r + z.i * z.i > 4)
					break ;
			}
			clr.r = 1.0 * (max_iter - iter) / max_iter * 0xff;
			clr.g = clr.r;
			clr.b = clr.r;

			int pos = count_w * pixel_bits / 8 + count_h * line_bytes;
			buffer[pos] = clr.b;
			buffer[pos + 1] = clr.g;
			buffer[pos + 2] = clr.r;

			/*
			c.r = -0.75;
			c.i = 0;
			z.r = (count_w - (WIN_W/2))/(WIN_W/4);
			z.i = (count_h - (WIN_H/2))/(WIN_H/4);
			iter = -1;
			while (++iter < 100)
			{
				tmp = z;
				z.r = tmp.r*tmp.r - tmp.i*tmp.i + c.r;
				z.i = 2*tmp.r*tmp.i + c.i;
				if (z.r*z.r + z.i*z.i > 4)
					break;
			}
			if (iter == 100)
				buffer[count_h * WIN_W + count_w] = 0xFFFF;
			*/
		}
	}
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_hook(vars.win, ON_KEYDOWN, 1L<<0, key_press, &vars);
	mlx_put_image_to_window(vars.mlx, vars.win, image, 0, 0);

	mlx_loop(vars.mlx);
}
