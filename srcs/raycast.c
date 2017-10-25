/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 16:24:11 by myang             #+#    #+#             */
/*   Updated: 2017/09/24 18:01:33 by myang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"
#include <math.h>

static void	ray_impact_dist(t_ray *ray, int *y, int *x)
{
	if (ray->raydir[0] < 0)
	{
		ray->step[0] = -1;
		ray->sidedist[0] = (ray->raypos[0] - *x) * ray->dist[0];
	}
	else
	{
		ray->step[0] = 1;
		ray->sidedist[0] = (1.0 + (*x - ray->raypos[0])) * ray->dist[0];
	}
	if (ray->raydir[1] < 0)
	{
		ray->step[1] = -1;
		ray->sidedist[1] = (ray->raypos[1] - *y) * ray->dist[1];
	}
	else
	{
		ray->step[1] = 1;
		ray->sidedist[1] = (1.0 + *y - ray->raypos[1]) * ray->dist[1];
	}
}

int			spewall_check(int curx, int cury, int **map)
{
	int	res;

	res = 0;
	if (map[cury][curx] >= 2)
		res = (map[cury][curx] == 3) ? 2 : 1;
	return (res);
}

static void	ray_impact(t_env *e, t_ray *ray, int *curx, int *cury)
{
	e->impact = 0;
	ray->dist[0] = sqrt(1 + (ray->raydir[1] *
				ray->raydir[1]) / (ray->raydir[0] * ray->raydir[0]));
	ray->dist[1] = sqrt(1 + (ray->raydir[0] *
				ray->raydir[0]) / (ray->raydir[1] * ray->raydir[1]));
	ray_impact_dist(ray, cury, curx);
	while (e->impact == 0)
	{
		if (ray->sidedist[0] < ray->sidedist[1])
		{
			ray->sidedist[0] += ray->dist[0];
			*curx += ray->step[0];
			e->cam->correct = (ray->step[0] < 0) ? 0 : 1;
		}
		else
		{
			ray->sidedist[1] += ray->dist[1];
			*cury += ray->step[1];
			e->cam->correct = 1;
			e->cam->correct = (ray->step[1] < 0) ? 2 : 3;
		}
		e->impact = (e->map->tabmap[*cury][*curx] != 0) ? 1 : 0;
	}
	e->cam->spewall = spewall_check(*curx, *cury, e->map->tabmap);
}

static void	ray_on_win_l(int x, t_env *e, t_ray *ray)
{
	double	camx;

	camx = (((2.0 * (double)x) / (double)WIN_L) - 1.0);
	ray->raypos[0] = e->cam->poscam[0];
	ray->raypos[1] = e->cam->poscam[1];
	ray->raydir[0] = e->cam->dircam[0] + (e->cam->dirwin[0] * camx);
	ray->raydir[1] = e->cam->dircam[1] + (e->cam->dirwin[1] * camx);
}

void		raycast_win_l(t_env *e, t_ray *ray)
{
	double	perps;
	int		x;
	int		curx;
	int		cury;

	x = 0;
	while (x < WIN_L)
	{
		ray_on_win_l(x, e, e->ray);
		curx = (int)(ray->raypos[0]);
		cury = (int)(ray->raypos[1]);
		ray_impact(e, e->ray, &curx, &cury);
		e->map->curx = curx;
		e->map->cury = cury;
		if (e->cam->correct <= 1)
			perps = (double)(curx - ray->raypos[0] +
					(1 - ray->step[0]) / 2.0) / ray->raydir[0];
		else
			perps = (double)(cury - ray->raypos[1] +
					(1 - ray->step[1]) / 2.0) / ray->raydir[1];
		draw_colo(e, x, perps);
		x++;
	}
}
