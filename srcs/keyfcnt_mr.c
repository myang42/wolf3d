/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyfcnt_mr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 16:41:30 by myang             #+#    #+#             */
/*   Updated: 2017/09/24 16:45:22 by myang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

int		mvmnt_camrott(t_env *e)
{
	double	oldrott;
	double	oldplan;
	double	rad;

	rad = 10.0 / 360 * 2 * M_PI;
	rad *= (e->key->rott_l == 1) ? -1 : 1;
	oldplan = e->cam->dirwin[0];
	oldrott = e->cam->dircam[0];
	e->cam->dircam[0] =
	e->cam->dircam[0] * cos(rad) - e->cam->dircam[1] * sin(rad);
	e->cam->dircam[1] = oldrott * sin(rad) + e->cam->dircam[1] * cos(rad);
	e->cam->dirwin[0] =
	e->cam->dirwin[0] * cos(rad) - e->cam->dirwin[1] * sin(rad);
	e->cam->dirwin[1] = oldplan * sin(rad) + e->cam->dirwin[1] * cos(rad);
	return (FALSE);
}

int		mvmnt_camdir(t_env *e, t_cam *cam, int x, int y)
{
	cam->varx = 0.0;
	cam->vary = 0.0;
	if (e->key->mvmnt_f == TRUE || e->key->mvmnt_b == TRUE)
	{
		cam->varx = (e->key->mvmnt_f == 1) ? cam->dircam[0] : -cam->dircam[0];
		cam->vary = (e->key->mvmnt_f == 1) ? cam->dircam[1] : -cam->dircam[1];
	}
	else if (e->key->mvmnt_r == TRUE || e->key->mvmnt_l == TRUE)
	{
		cam->varx = (e->key->mvmnt_r == 1) ? cam->dirwin[0] : -cam->dirwin[0];
		cam->vary = (e->key->mvmnt_r == 1) ? cam->dirwin[1] : -cam->dirwin[1];
	}
	if (e->map->tabmap[y][(int)(cam->poscam[0] +
				(cam->varx * cam->vit) * 2)] == 2 ||
			e->map->tabmap[(int)(cam->poscam[1] +
				(cam->vary * cam->vit) * 2)][x] == 2)
		e->dmg = TRUE;
	if (e->map->tabmap[y][(int)(cam->poscam[0] + cam->varx * cam->vit)] == 0 ||
	e->map->tabmap[y][(int)(cam->poscam[0] + cam->varx * cam->vit)] == 3)
		cam->poscam[0] += cam->varx * cam->vit;
	if (e->map->tabmap[(int)(cam->poscam[1] + cam->vary * cam->vit)][x] == 0 ||
	e->map->tabmap[(int)(cam->poscam[1] + cam->vary * cam->vit)][x] == 3)
		cam->poscam[1] += cam->vary * cam->vit;
	return (TRUE);
}

void	key_pressed(t_env *e, int key)
{
	(key == KEY_W) ? e->key->mvmnt_f = TRUE : 0;
	(key == KEY_S) ? e->key->mvmnt_b = TRUE : 0;
	(key == KEY_D) ? e->key->mvmnt_r = TRUE : 0;
	(key == KEY_A) ? e->key->mvmnt_l = TRUE : 0;
	(key == KEY_E) ? e->key->rott_r = TRUE : 0;
	(key == KEY_Q) ? e->key->rott_l = TRUE : 0;
	if (key == KEY_W || key == KEY_S || key == KEY_D || key == KEY_A)
		e->inv->tokken->nbr += 1;
}
