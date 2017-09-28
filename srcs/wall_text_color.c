/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_text_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 18:09:27 by myang             #+#    #+#             */
/*   Updated: 2017/09/24 18:21:29 by myang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void		text_to_bts(t_env *e, t_img *xpmt, int x, int y)
{
	int		r;
	int		g;
	int		b;
	double	var;
	double	tmp;

	tmp = e->ray->perps;
	tmp = (tmp > 8) ? 8 : tmp;
	var = 1 - (tmp / 8);
	r = ABS((xpmt->bts[(xpmt->xy[0] * xpmt->size_line) +
				((xpmt->bpp / 8) * xpmt->xy[1]) + 2]));
	g = ABS((xpmt->bts[(xpmt->xy[0] * xpmt->size_line) +
				((xpmt->bpp / 8) * xpmt->xy[1]) + 1]));
	b = ABS((xpmt->bts[(xpmt->xy[0] * xpmt->size_line) +
				((xpmt->bpp / 8) * xpmt->xy[1]) + 0]));
	e->bts[(y * e->img->size_line) + ((e->img->bpp / 8) * x) + 2] =
		r * var + 0x0B * (1 - var);
	e->bts[(y * e->img->size_line) + ((e->img->bpp / 8) * x) + 1] =
		g * var + 0x0B * (1 - var);
	e->bts[(y * e->img->size_line) + ((e->img->bpp / 8) * x) + 0] =
		b * var + 0x0B * (1 - var);
}

static void	text_to_bts_cf(t_env *e, t_img *xpmt, int x, int y)
{
	int		r;
	int		g;
	int		b;
	double	var;
	double	tmp;

	xpmt->xy[0] %= xpmt->textx;
	xpmt->xy[1] %= xpmt->texty;
	tmp = (y > WIN_H / 2) ? WIN_H - y : y;
	tmp = (tmp > WIN_H / 2.5) ? WIN_H / 2.5 : tmp;
	var = 1 - (tmp / (WIN_H / 2.5));
	r = ABS((xpmt->bts[(xpmt->xy[0] * xpmt->size_line) +
				((xpmt->bpp / 8) * xpmt->xy[1]) + 2]));
	g = ABS((xpmt->bts[(xpmt->xy[0] * xpmt->size_line) +
				((xpmt->bpp / 8) * xpmt->xy[1]) + 1]));
	b = ABS((xpmt->bts[(xpmt->xy[0] * xpmt->size_line) +
				((xpmt->bpp / 8) * xpmt->xy[1]) + 0]));
	e->bts[(y * e->img->size_line) + ((e->img->bpp / 8) * x) + 2] =
		r * var + 0x0B * (1 - var);
	e->bts[(y * e->img->size_line) + ((e->img->bpp / 8) * x) + 1] =
		g * var + 0x0B * (1 - var);
	e->bts[(y * e->img->size_line) + ((e->img->bpp / 8) * x) + 0] =
		b * var + 0x0B * (1 - var);
}

void		wall_or_cf(t_env *e, int y, int cfw)
{
	t_img	*xpmt;

	(cfw == TRUE) ? val_floor_ceilling(e, y) : 0;
	if (cfw == FALSE)
	{
		if (!(xpmt = select_xpm(e, e->text->walltextt)))
			exit(EXIT_FAILURE);
		xpmt->xy[0] = xpmt->texty * (y - (WIN_H - e->ray->height_l) / 2) /
			e->ray->height_l;
		xpmt->xy[1] = (int)(e->ray->wallx * xpmt->textx);
		text_to_bts(e, xpmt, e->map->pxx, y);
	}
	else if (cfw == TRUE)
	{
		e->text->xpm->xpm_t5->xy[1] = ((int)(e->img->cfx *
					e->text->xpm->xpm_t5->textx) / 2);
		e->text->xpm->xpm_t5->xy[0] = ((int)(e->img->cfy *
					e->text->xpm->xpm_t5->texty) / 2);
		text_to_bts_cf(e, e->text->xpm->xpm_t5, e->map->pxx, y);
		e->text->xpm->xpm_t6->xy[1] = ((int)(e->img->cfx *
					e->text->xpm->xpm_t6->textx) / 2);
		e->text->xpm->xpm_t6->xy[0] = ((int)(e->img->cfy *
					e->text->xpm->xpm_t6->texty) / 2);
		text_to_bts_cf(e, e->text->xpm->xpm_t6, e->map->pxx, WIN_H - y);
	}
}

void		text_put_img(t_env *e, int y, int cfw)
{
	if (e->text->color_or_text == TRUE)
		wall_or_cf(e, y, cfw);
	else if (e->text->color_or_text == 0 || e->text->color_or_text == 2)
	{
		if (e->text->color_or_text == 2)
		{
			e->text->xpm->skybox->xy[0] = (int)e->map->pxy;
			e->text->xpm->skybox->xy[1] = (int)e->map->pxx;
			text_to_bts(e, e->text->xpm->skybox, e->map->pxx, WIN_H - y - 1);
		}
		else
			pix_put_cf(e, WIN_H - 1 - y, e->map->pxx, PINK);
		pix_put_cf(e, y, e->map->pxx, GREY);
	}
}

void		basiccolor_or_text(t_env *e, int x, int y)
{
	int color;

	if (e->text->color_or_text != TRUE)
	{
		color = RED_D;
		color = (e->cam->correct == 1) ? BLUE_D : color;
		color = (e->cam->correct == 2) ? YELLOW_L : color;
		color = (e->cam->correct == 3) ? GREEN_D : color;
		color = (e->cam->spewall == TRUE) ? WHITE : color;
		pix_put_img(e, y, x, color);
	}
	else
		text_put_img(e, y, FALSE);
}
