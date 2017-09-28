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
		e->img->i_img = mlx_new_image(e->mlx, WIN_L, WIN_H);
		e->bts = mlx_get_data_addr(e->img->i_img, \
			&e->img->bpp, &e->img->size_line, &e->img->endian);
	}
}

void		clear_struct_displayed(t_env *e, int call)
{
	(call == TRUE) ? clear_all(e, FALSE) : 0;
	free(e->mmapdisplay);
	free(e->ray);
	free(e->key);
	free(e->text->xpm->window_1);
	free(e->text->xpm->minimap);
	free(e->text->xpm->gameover);
	free(e->text->xpm->xpm_t1);
	free(e->text->xpm->xpm_t2);
	free(e->text->xpm->xpm_t3);
	free(e->text->xpm->xpm_t4);
	free(e->text->xpm->xpm_t7);
	free(e->text->xpm->xpm_t6);
	free(e->text->xpm->xpm_t5);
	free(e->text->xpm->xpm_pv1);
	free(e->text->xpm->xpm_pv2);
	free(e->text->xpm->xpm_pv3);
	free(e->text->xpm->xpm_wicon);
	free(e->text->xpm->xpm_weapon);
	free(e->text->xpm);
	free(e->text);
	free(e->inv);
}

void		clear_struct_init(t_env *e)
{
	free(e->cam);
	free(e->map->tabmap);
	free(e->map);
	free(e->img);
}
