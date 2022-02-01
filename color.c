/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 22:36:11 by jihoh             #+#    #+#             */
/*   Updated: 2022/02/01 23:10:10 by jihoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_clr	set_clr(unsigned char r, unsigned char g, unsigned char b)
{
	t_clr	ret;

	ret.r = r;
	ret.g = g;
	ret.b = b;
	return (ret);
}

void	init_clrset(t_clrset *clrset)
{
	clrset->clrset1[0] = set_clr(0, 7, 100);
	clrset->clrset1[1] = set_clr(32, 107, 203);
	clrset->clrset1[2] = set_clr(237, 255, 255);
	clrset->clrset1[3] = set_clr(255, 170, 0);
	clrset->clrset1[4] = set_clr(0, 2, 0);
	clrset->clrset2[0] = set_clr(0, 0, 0);
	clrset->clrset2[1] = set_clr(213, 67, 31);
	clrset->clrset2[2] = set_clr(251, 255, 121);
	clrset->clrset2[3] = set_clr(62, 223, 89);
	clrset->clrset2[4] = set_clr(43, 30, 218);
}

t_clr	linear_interpolation(t_clr v, t_clr u, double a)
{
	double	b;

	b = 1 - a;
	return (set_clr(b * v.r + a * u.r, b * v.g + a * u.g, b * v.b + a * u.b));
}

t_clr	get_color(int iter, t_frctl *frctl, t_clr *clrset)
{
	double	mu;
	size_t	i_mu;
	t_clr	clr1;
	t_clr	clr2;
	t_clr	ret;

	if (iter == frctl->itermax)
		iter = 0;
	mu = 1.0 * iter / frctl->itermax * 4;
	i_mu = (size_t)mu;
	clr1 = clrset[i_mu];
	if (i_mu + 1 < 4)
		clr2 = clrset[i_mu + 1];
	else
		clr2 = clrset[4];
	ret = linear_interpolation(clr1, clr2, mu - i_mu);
	return (ret);
}
