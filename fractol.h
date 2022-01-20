/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:56:36 by jihoh             #+#    #+#             */
/*   Updated: 2022/01/20 19:07:54 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <mlx.h>

# define WIN_H   800
# define WIN_W   800

typedef struct	s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}				t_color;

typedef struct	s_cmplx
{
	int		r; //real
	int		i; //img
}				t_cmplx;

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bpp; //bits_per_pixel
	int		line_length;
	int		endian;
}				t_img;

typedef struct	s_frctl 
{
	void	*mlx;
	void	*win;
	int		x;
	int		y;
	int		itermax;
	double	xmin;
	double	xmax;
	double	ymin;
	double	ymax;
}				t_frctl;

#endif
