/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:56:36 by jihoh             #+#    #+#             */
/*   Updated: 2022/01/23 16:23:47 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <mlx.h>

# define WIN_W	960
# define WIN_H	540

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
	double		cr; //real
	double		ci; //img
	double		zr;
	double		zi;
	double		tmpr;
}				t_cmplx;

typedef struct	s_point {
	int	x;
	int	y;
}				t_point;

typedef struct	s_data {
	void	*img;
	char	*buff;
	int		bpp; //bits_per_pixel;
	int		bpl; //bytes_per_line;
	int		endian;
}				t_data;

typedef struct	s_frctl {
	void	*mlx;
	void	*win;
	double	rmin;
	double	rmax;
	double	imin;
	double	imax;
	int		itermax;
}				t_frctl;

void	init_vars(t_frctl *frctl, t_data *data);
int		key_press(int keycode, t_frctl *vars);
void	put_color(t_data *data, t_point point, t_clr clr);
void	mandelbrot(t_frctl *frctl, t_data *data, t_point point);
void	draw_fractol(t_frctl *frctl, t_data *data);

#endif
