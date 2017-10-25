/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 18:03:45 by myang             #+#    #+#             */
/*   Updated: 2017/09/23 18:05:07 by myang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

static void	clear_spr(t_env *e, t_img *spr)
{
	ft_bzero(spr->bts, ft_strlen(spr->bts));
	mlx_destroy_image(e->mlx, spr->i_img);
}

static void	clear_xpm(t_env *e, t_xpm *xpm)
{
	clear_spr(e, xpm->xpm_t1);
	clear_spr(e, xpm->xpm_t2);
	clear_spr(e, xpm->xpm_t3);
	clear_spr(e, xpm->xpm_t4);
	clear_spr(e, xpm->xpm_t5);
	clear_spr(e, xpm->xpm_t6);
	clear_spr(e, xpm->window_1);
	clear_spr(e, xpm->xpm_pv3);
	clear_spr(e, xpm->xpm_pv2);
	clear_spr(e, xpm->xpm_pv1);
	clear_spr(e, xpm->xpm_weapon);
	clear_spr(e, xpm->minimap);
}

void		clear_all(t_env *e, int call)
{
	mlx_clear_window(e->mlx, e->win);
	ft_bzero(e->bts, ft_strlen(e->bts));
	clear_xpm(e, e->text->xpm);
	mlx_destroy_image(e->mlx, e->img->i_img);
	if (e->inv->pv->nbr > 0)
	{
		xpmt_secur(e);
		interface(e);
		interface_mmap(e);
	}
	if (call == FALSE)
	{
		if (!(e->img->i_img = mlx_new_image(e->mlx, WIN_L, WIN_H)))
			quit_exe(e, FALSE);
		if (!(e->bts = mlx_get_data_addr(e->img->i_img,
			&e->img->bpp, &e->img->size_line, &e->img->endian)))
			quit_exe(e, FALSE);
	}
}

void		clear_struct_displayed(t_env *e, int call)
{
	(call == TRUE) ? clear_all(e, FALSE) : 0;
}

void		clear_struct_init(t_env *e)
{
	if (e->cam)
		free(e->cam);
	if (e->map->tabmap)
		free(e->map->tabmap);
	if (e->map)
		free(e->map);
	if (e->img)
		free(e->img);
}
