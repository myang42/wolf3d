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

double		wallx_val(t_env *e)
{
	double	wallx;

	if (e->cam->correct < 2)
		wallx = e->ray->raypos[1] + e->ray->perps * e->ray->raydir[1];
	else
		wallx = e->ray->raypos[0] + e->ray->perps * e->ray->raydir[0];
	wallx -= (int)(wallx);
	return (wallx);
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

void		basiccolor_or_text(t_env *e, int x, int y)
{
	int color;

	if (e->text->color_or_text != TRUE)
	{
		color = RED_D;
		color = (e->cam->correct == 1) ? BLUE_D : color;
		color = (e->cam->correct == 2) ? YELLOW_L : color;
		color = (e->cam->correct == 3) ? GREEN_D : color;
		color = (e->cam->spewall == 1) ? WHITE : color;
		color = (e->cam->spewall == 2) ? RED_L : color;
		pix_put_img(e, y, x, color);
	}
	else
		text_put_img(e, y, FALSE);
}
