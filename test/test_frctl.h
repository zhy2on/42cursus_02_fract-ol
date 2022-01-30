/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_frctl.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:56:36 by jihoh             #+#    #+#             */
/*   Updated: 2022/01/30 19:28:44 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_FRCTL_H
# define TEST_FRCTL_H

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
	LEFT_ARROW= 123,
	RIGHT_ARROW = 124,
	UP_ARROW = 126,
	DOWN_ARROW = 125,
	LEFT_CLICK = 1
};

typedef struct s_clr
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
}				t_clr;

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
	void	*mlx;
	void	*win;
	double	xmin;
	double	xmax;
	double	ymin;
	double	ymax;
	double	offx;
	double	offy;
	double	zoom;
	int		itermax;
	t_data	data;
}				t_frctl;

void	screen_to_world(t_point *point, t_cmplx *cmplx, t_frctl *fr);
void	init_vars(t_frctl *frctl);
int		key_press(int keycode, t_frctl *vars);
void	put_color(t_data *data, t_point point, t_clr clr);
void	mandelbrot(t_frctl *frctl, t_data *data, t_point point);
void	draw_fractol(t_frctl *frctl, t_data *data);
void	zoom(t_frctl *frctl, t_data *data, int x, int y);
int		mouse_hook(int button, int x, int y, t_frctl *frctl);

#endif
