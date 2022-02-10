/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:56:36 by jihoh             #+#    #+#             */
/*   Updated: 2022/02/10 18:08:17 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <mlx.h>
# include <unistd.h>

# define WIN_W	1280
# define WIN_H	720

enum {
	ON_KEYDOWN = 2,
	ON_MOUSEDOWN = 4,
	SCROLL_DOWN = 4,
	SCROLL_UP = 5,
	KEY_ESC = 53,
	KEY_1 = 18,
	KEY_2 = 19,
	KEY_3 = 20,
	LEFT_ARROW= 123,
	RIGHT_ARROW = 124,
	UP_ARROW = 126,
	DOWN_ARROW = 125,
};

typedef struct s_clr
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}				t_clr;

typedef struct s_clrset
{
	int		clrsize;
	t_clr	clrset1[5];
	t_clr	clrset2[6];
	t_clr	clrset3[7];
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
	char		is_use_param;
	double		rmin;
	double		rmax;
	double		imin;
	double		imax;
	double		zoom;
	double		offx;
	double		offy;
	int			itermax;
	t_cmplx		julia_c;
	t_clrset	clrset;
	t_data		data;
}				t_frctl;

/*
*** main.c ***
*/
double	ft_atof(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
void	init_vars(t_frctl *frctl, char **argv);
void	init_viewset(t_frctl *frctl);

/*
*** hook.c ***
*/
void	world_to_screen(t_cmplx *cmplx, t_point *point, t_frctl *fr);
int		key_hook(int keycode, t_frctl *frctl);
int		mouse_hook(int button, int x, int y, t_frctl *frctl);

/*
*** fractol.c ***
*/
void	screen_to_world(t_point *point, t_cmplx *cmplx, t_frctl *fr);
void	julia(t_frctl *frctl, t_data *data, t_point point);
void	mandelbrot(t_frctl *frctl, t_data *data, t_point point);
void	spider(t_frctl *frctl, t_data *data, t_point point);
void	draw_fractol(t_frctl *frctl, t_data *data);

/*
*** color.c ***
*/
void	put_color(t_data *data, t_point point, t_clr clr);
t_clr	set_color(unsigned char r, unsigned char g, unsigned char b);
void	init_clrset(t_clrset *clrset);
t_clr	linear_interpolation(t_clr v, t_clr u, double a);
t_clr	get_color(int iter, t_frctl *frctl, t_clrset *clrset);

#endif
