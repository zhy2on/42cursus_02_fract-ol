/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:56:36 by jihoh             #+#    #+#             */
/*   Updated: 2022/02/01 23:16:41 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <mlx.h>
# include <stdio.h>

# define WIN_W	960
# define WIN_H	540

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	KEY_ESC = 53,
	LEFT_ARROW= 123,
	RIGHT_ARROW = 124,
	UP_ARROW = 126,
	DOWN_ARROW = 125,
	LEFT_CLICK = 1
};

typedef struct s_clr
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}				t_clr;

typedef struct s_clrset
{
	t_clr	clrset1[5];
	t_clr	clrset2[6];
}				t_clrset;

typedef struct s_cmplx
{
	double	r;
	double	i;
}				t_cmplx;

typedef struct s_point {
	int	x;
	int	y;
}				t_point;

typedef struct s_data {
	void	*img;
	char	*buff;
	int		bpp;
	int		bpl;
	int		endian;
}				t_data;

typedef struct s_frctl {
	void		*mlx;
	void		*win;
	char		type;
	double		xmin;
	double		xmax;
	double		ymin;
	double		ymax;
	double		offx;
	double		offy;
	double		zoom;
	int			itermax;
	t_clrset	clrset;
	t_data		data;
}				t_frctl;

int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	draw_fractol(t_frctl *frctl, t_data *data);
void	init_vars(t_frctl *frctl, char *argv);
void	init_viewset(t_frctl *frctl);
void	screen_to_world(t_point *point, t_cmplx *cmplx, t_frctl *fr);
void	put_color(t_data *data, t_point point, t_clr clr);
void	julia(t_frctl *frctl, t_data *data, t_point point);
void	mandelbrot(t_frctl *frctl, t_data *data, t_point point);
void	spider(t_frctl *frctl, t_data *data, t_point point);
int		key_hook(int keycode, t_frctl *frctl);
int		mouse_hook(int button, int x, int y, t_frctl *frctl);
t_clr	set_clr(unsigned char r, unsigned char g, unsigned char b);
void	init_clrset(t_clrset *clrset);
t_clr	linear_interpolation(t_clr v, t_clr u, double a);
t_clr	get_color(int iter, t_frctl *frctl, t_clr *clrset);

#endif
