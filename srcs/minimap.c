/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 17:51:34 by myang             #+#    #+#             */
/*   Updated: 2017/09/24 17:54:41 by myang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

static void	def_valfs(t_mmapdisplay *frst, t_mmapdisplay *scnd, int n1, int n2)
{
	frst->pxx = n1 * (150 / 10);
	scnd->pxx = (n1 == 10) ? frst->pxx : (n1 + 1) * 150 / 10;
	frst->pxy = n2 * (150 / 10);
	scnd->pxy = (n2 == 10) ? frst->pxy : (n2 + 1) * 150 / 10;
}

static void	pxl_mmap(t_mmapdisplay *frst, t_mmapdisplay *scnd, int n1, t_img *i)
{
	while (frst->pxx != scnd->pxx || frst->pxy != scnd->pxy)
	{
		draw_pxl_mmap(i, frst->pxy, frst->pxx, WHITE);
		if (frst->pxx == scnd->pxx)
		{
			frst->pxx = n1 * 150 / 10;
			frst->pxy += 1;
		}
		else
			frst->pxx += 1;
	}
}

static void	define_coord_mmap(t_map *map, t_img *map_i)
{
	t_mmapdisplay	frst;
	t_mmapdisplay	scnd;
	int				n1;
	int				n2;

	n1 = 0;
	n2 = 0;
	while (n2 <= 9)
	{
		while (n1 <= 9)
		{
			if (map->minimap[n2][n1] == 0)
			{
				def_valfs(&frst, &scnd, n1, n2);
				pxl_mmap(&frst, &scnd, n1, map_i);
			}
			n1 += 1;
		}
		n1 = 0;
		n2 += 1;
	}
}

void		draw_mmap(t_cam *cam, t_env *e, t_map *map)
{
	t_mmapdisplay	pxl;
	t_mmapdisplay	sz;

	pxl.pxx = 0;
	pxl.pxy = 0;
	while (pxl.pxy <= 9)
	{
		sz.pxy = cam->poscam[1] - 4 + pxl.pxy;
		sz.pxy = (sz.pxy >= e->map->s_y) ? -1 : sz.pxy;
		while (pxl.pxx <= 9)
		{
			sz.pxx = cam->poscam[0] - 4 + pxl.pxx;
			sz.pxx = (sz.pxx >= e->map->s_x) ? -1 : sz.pxx;
			if (sz.pxx >= 0 && sz.pxy >= 0 && map->tabmap[sz.pxy][sz.pxx] == 0)
				map->minimap[pxl.pxy][pxl.pxx] = map->tabmap[sz.pxy][sz.pxx];
			else
				map->minimap[pxl.pxy][pxl.pxx] = 1;
			pxl.pxx += 1;
		}
		pxl.pxx = 0;
		pxl.pxy += 1;
	}
	define_coord_mmap(map, e->text->xpm->minimap);
	def_playermmaap(e);
}
