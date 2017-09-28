/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceilling_floor_text.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 18:01:04 by myang             #+#    #+#             */
/*   Updated: 2017/09/23 18:03:27 by myang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void	floor_val(t_env *e, int curx, int cury, double wallx)
{
	if (e->cam->correct <= 1 && e->ray->raydir[0] > 0)
	{
		e->ray->floorval[0] = curx;
		e->ray->floorval[1] = cury + wallx;
	}
	else if (e->cam->correct <= 1 && e->ray->raydir[0] < 0)
	{
		e->ray->floorval[0] = curx + 1.0;
		e->ray->floorval[1] = cury + wallx;
	}
	else if (e->cam->correct >= 2 && e->ray->raydir[1] > 0)
	{
		e->ray->floorval[0] = curx + wallx;
		e->ray->floorval[1] = cury;
	}
	else
	{
		e->ray->floorval[0] = curx + wallx;
		e->ray->floorval[1] = cury + 1.0;
	}
}

void	val_floor_ceilling(t_env *e, int y)
{
	double	dist;
	double	w;

	dist = (double)((WIN_H) / (2.0 * y - WIN_H));
	w = (double)(dist / e->ray->perps);
	e->img->cfx = (w * e->ray->floorval[0] + (1.0 - w) * e->cam->poscam[0]);
	e->img->cfy = (w * e->ray->floorval[1] + (1.0 - w) * e->cam->poscam[1]);
}

void	skybox(t_env *e)
{
	e->text->xpm->skybox = (t_img*)malloc(sizeof(t_img));
	sprite_data(e->text->xpm->skybox, "./textures/skybox.xpm", e);
}
