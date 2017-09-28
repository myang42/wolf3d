/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 18:06:51 by myang             #+#    #+#             */
/*   Updated: 2017/09/24 16:25:13 by myang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void		draw_pxl_mmap(t_img *mmap, int y, int x, int color)
{
	int	r;
	int	g;
	int	b;

	r = (color & 0xFF0000) >> 16;
	g = (color & 0xFF00) >> 8;
	b = (color & 0xFF);
	if (y + 1 > 0 && x >= 0 && y + 1 < 150 && x < 150)
	{
		mmap->bts[(y * mmap->size_line) + ((mmap->bpp / 8) * x) + 2] = r;
		mmap->bts[(y * mmap->size_line) + ((mmap->bpp / 8) * x) + 1] = g;
		mmap->bts[(y * mmap->size_line) + ((mmap->bpp / 8) * x)] = b;
	}
}

void		pix_put_img(t_env *e, int y, int x, int color)
{
	int		r;
	int		g;
	int		b;
	double	var;
	double	tmp;

	tmp = e->ray->perps;
	tmp = (tmp > 8) ? 8 : tmp;
	var = 1 - (tmp / 8);
	r = (color & 0xFF0000) >> 16;
	g = (color & 0xFF00) >> 8;
	b = (color & 0xFF);
	if (y + 1 > 0 && x >= 0 && y + 1 < WIN_H && x < WIN_L)
	{
		e->bts[(y * e->img->size_line) + ((e->img->bpp / 8) * x) + 2] =
			r * var + 0x0B * (1 - var);
		e->bts[(y * e->img->size_line) + ((e->img->bpp / 8) * x) + 1] =
			g * var + 0x0B * (1 - var);
		e->bts[(y * e->img->size_line) + ((e->img->bpp / 8) * x) + 0] =
			b * var + 0x0B * (1 - var);
	}
}

void		pix_put_cf(t_env *e, int y, int x, int color)
{
	int		r;
	int		g;
	int		b;
	double	var;
	double	tmp;

	tmp = (y > WIN_H / 2) ? WIN_H - y : y;
	tmp = (tmp > WIN_H / 2.5) ? WIN_H / 2.5 : tmp;
	var = 1 - (tmp / (WIN_H / 2.5));
	r = (color & 0xFF0000) >> 16;
	g = (color & 0xFF00) >> 8;
	b = (color & 0xFF);
	if (y + 1 > 0 && x >= 0 && y + 1 < WIN_H && x < WIN_L)
	{
		e->bts[(y * e->img->size_line) + ((e->img->bpp / 8) * x) + 2] =
			r * var + 0x0B * (1 - var);
		e->bts[(y * e->img->size_line) + ((e->img->bpp / 8) * x) + 1] =
			g * var + 0x0B * (1 - var);
		e->bts[(y * e->img->size_line) + ((e->img->bpp / 8) * x) + 0] =
			b * var + 0x0B * (1 - var);
	}
}

static int	heigh_colo(int *draw, double perps)
{
	int	height_l;

	height_l = (int)(WIN_H / perps);
	height_l = (height_l < 0) ? -height_l : height_l;
	draw[0] = (WIN_H - height_l) / 2;
	draw[1] = draw[0] + height_l;
	if (draw[0] < 0)
		draw[0] = 0;
	if (draw[1] >= WIN_H)
		draw[1] = WIN_H;
	return (height_l);
}

void		draw_colo(t_env *e, int x, double perps)
{
	int	draw[2];

	e->ray->height_l = heigh_colo(draw, perps);
	e->ray->perps = perps;
	e->map->pxy = draw[0];
	e->map->pxx = x;
	e->ray->wally = e->map->pxy;
	e->ray->wallx = wallx_val(e);
	while (e->map->pxy < draw[1])
	{
		basiccolor_or_text(e, x, e->map->pxy);
		e->map->pxy += 1;
	}
	floor_val(e, e->map->curx, e->map->cury, e->ray->wallx);
	while (e->map->pxy < WIN_H)
	{
		text_put_img(e, e->map->pxy, 1);
		e->map->pxy += 1;
	}
}
