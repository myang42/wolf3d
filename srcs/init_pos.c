/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/12 18:30:22 by myang             #+#    #+#             */
/*   Updated: 2017/09/24 16:38:23 by myang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

int			start_pos(t_env *e, t_map *map)
{
	int		posx;
	int		posy;

	posy = map->s_y - 1;
	posx = map->s_x - 1;
	while (posy > 0 && map->tabmap[posy][posx] != 0)
	{
		while (posx > 0 && map->tabmap[posy][posx] != 0)
			posx -= 1;
		if (map->tabmap[posy][posx] == 0)
			break ;
		posy -= 1;
		posx = map->s_x - 1;
	}
	if (posx > 0 && posy > 0)
	{
		e->cam->poscam[0] = posx + 0.25;
		e->cam->poscam[1] = posy + 0.25;
		return (1);
	}
	return (0);
}

void		mmapdisplay_valu(t_mmapdisplay *player, t_mmapdisplay *visu,
		t_mmapdisplay *s, t_mmapdisplay *d)
{
	d->pxx = ABS((visu->pxx - player->pxx));
	d->pxy = ABS((visu->pxy - player->pxy));
	s->pxx = (player->pxx < visu->pxx) ? 1 : -1;
	s->pxy = (player->pxy < visu->pxy) ? 1 : -1;
}

static void	pxl_mmap(t_env *e, t_mmapdisplay *player, int l)
{
	draw_pxl_mmap(e->text->xpm->minimap, player->pxy - 7,
			player->pxx + l - 7, PINK);
	draw_pxl_mmap(e->text->xpm->minimap, player->pxy - 7,
			player->pxx - l - 7, PINK);
}

static void	mmappos(t_mmapdisplay *player, t_mmapdisplay *visu, int l, t_env *e)
{
	t_mmapdisplay	var;
	t_mmapdisplay	d;
	t_mmapdisplay	s;

	mmapdisplay_valu(player, visu, &s, &d);
	var.pxx = ((d.pxx > d.pxy) ? d.pxx : -d.pxy) / 2;
	while ((player->pxx != visu->pxx) || (player->pxy != visu->pxy))
	{
		l = -1;
		while (++l <= 2)
			pxl_mmap(e, player, l);
		var.pxy = var.pxx;
		if (var.pxy > -d.pxx)
		{
			var.pxx -= d.pxy;
			player->pxx += s.pxx;
		}
		if (var.pxy < d.pxy)
		{
			var.pxx += d.pxx;
			player->pxy += s.pxy;
		}
	}
}

void		def_playermmaap(t_env *e)
{
	t_mmapdisplay	player;
	t_mmapdisplay	visu;

	player.pxx = (150 / 2);
	player.pxy = (150 / 2);
	visu.pxx = player.pxx + 20 * e->cam->dircam[0];
	visu.pxy = player.pxy + 20 * e->cam->dircam[1];
	mmappos(&player, &visu, -1, e);
	player.pxx = (150 / 2) - 5;
	player.pxy = (150 / 2) - 5;
	while (player.pxx != (150 / 2 + 5) || player.pxy != (150 / 2 + 5))
	{
		draw_pxl_mmap(e->text->xpm->minimap,
				player.pxy - 7, player.pxx - 7, BLUE);
		if (player.pxx == 150 / 2 + 5)
		{
			player.pxy += 1;
			player.pxx = 150 / 2 - 5;
		}
		else
			player.pxx += 1;
	}
}
