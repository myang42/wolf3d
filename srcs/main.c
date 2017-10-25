/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 13:42:36 by myang             #+#    #+#             */
/*   Updated: 2017/10/25 15:42:50 by myang            ###   ########.fr       */
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

int			main(int ar, char **ac)
{
	t_env	e;

	if (ar > 1 && ac[1] != NULL)
	{
		init_struct(&e);
		init_cam(&e);
		readfile(&e, ac[1]);
		if (map_error(&e, e.map) != 1)
			quit_error(&e);
		start_pos(&e, e.map) > 0 ? 0 : quit_error(&e);
		secur_init(&e);
		raycast_win_l(&e, e.ray);
		interface_mmap(&e);
		interface(&e);
		mlx_put_image_to_window(e.mlx, e.win, e.img->i_img, 0, 0);
		interface_txt(&e, e.text->xpm);
		music_bgm(&e);
		mlx_do_key_autorepeaton(e.mlx);
		mlx_hook(e.win, 17, (1L << 17), red_cross, &e);
		mlx_hook(e.win, 2, 0, &keyfonc, &e);
		mlx_loop(e.mlx);
	}
	else
		msg_error();
	return (0);
}
