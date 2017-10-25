/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secur_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 18:02:06 by myang             #+#    #+#             */
/*   Updated: 2017/09/24 18:05:02 by myang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void	xpmt_secur(t_env *e)
{
	walltexturing(e, 8, e->text->xpm->xpm_t0);
	walltexturing(e, 1, e->text->xpm->xpm_t1);
	walltexturing(e, 2, e->text->xpm->xpm_t2);
	walltexturing(e, 3, e->text->xpm->xpm_t3);
	walltexturing(e, 4, e->text->xpm->xpm_t4);
	walltexturing(e, 5, e->text->xpm->xpm_t5);
	walltexturing(e, 6, e->text->xpm->xpm_t6);
	walltexturing(e, 7, e->text->xpm->xpm_t7);
}

void	init_struct(t_env *e)
{
	if (!(e->cam = (t_cam*)malloc(sizeof(t_cam))))
		quit_error(e);
	if (!(e->map = (t_map*)malloc(sizeof(t_map))))
		quit_error(e);
	if (!(e->img = (t_img*)malloc(sizeof(t_img))))
		quit_error(e);
}

void	init_bag(t_inv *inv, t_env *e)
{
	(!(inv->tokken = (t_inv*)malloc(sizeof(t_inv)))) ? quit_exe(e, FALSE) : 0;
	(!(inv->ammo = (t_inv*)malloc(sizeof(t_inv)))) ? quit_exe(e, FALSE) : 0;
	(!(inv->pv = (t_inv*)malloc(sizeof(t_inv)))) ? quit_exe(e, FALSE) : 0;
	(!(inv->weapon = (t_inv*)malloc(sizeof(t_inv)))) ? quit_exe(e, FALSE) : 0;
	(!(e->text->xpm->xpm_pv1 = (t_img*)malloc(sizeof(t_img)))) ?
		quit_exe(e, FALSE) : 0;
	(!(e->text->xpm->xpm_pv2 = (t_img*)malloc(sizeof(t_img)))) ?
		quit_exe(e, FALSE) : 0;
	(!(e->text->xpm->xpm_pv3 = (t_img*)malloc(sizeof(t_img)))) ?
		quit_exe(e, FALSE) : 0;
	(!(e->text->xpm->xpm_weapon = (t_img*)malloc(sizeof(t_img)))) ?
		quit_exe(e, FALSE) : 0;
	(!(e->text->xpm->xpm_wicon = (t_img*)malloc(sizeof(t_img)))) ?
		quit_exe(e, FALSE) : 0;
	inv->weapon->nbr = 0;
	e->inv->tokken->nbr = 0;
	inv->ammo->nbr = 5;
	inv->pv->nbr = 12;
}

void	init_struct_displayed(t_env *e)
{
	(!(e->ray = (t_ray*)malloc(sizeof(t_ray)))) ? quit_exe(e, FALSE) : 0;
	(!(e->key = (t_key*)malloc(sizeof(t_key)))) ? quit_exe(e, FALSE) : 0;
	(!(e->text = (t_text*)malloc(sizeof(t_text)))) ? quit_exe(e, FALSE) : 0;
	(!(e->mmapdisplay = (t_mmapdisplay*)malloc(sizeof(t_mmapdisplay)))) ?
		quit_exe(e, FALSE) : 0;
	(!(e->text->xpm = (t_xpm*)malloc(sizeof(t_xpm)))) ? quit_exe(e, FALSE) : 0;
	(!(e->text->xpm->window_1 = (t_img*)malloc(sizeof(t_img)))) ?
		quit_exe(e, FALSE) : 0;
	(!(e->text->xpm->minimap = (t_img*)malloc(sizeof(t_img)))) ?
		quit_exe(e, FALSE) : 0;
	(!(e->text->xpm->gameover = (t_img*)malloc(sizeof(t_img)))) ?
		quit_exe(e, FALSE) : 0;
	(!(e->text->xpm->arrival = (t_img*)malloc(sizeof(t_img)))) ?
		quit_exe(e, FALSE) : 0;
	(!(e->inv = (t_inv*)malloc(sizeof(t_inv)))) ? quit_exe(e, FALSE) : 0;
}

void	secur_init(t_env *e)
{
	init_struct_displayed(e);
	init_bag(e->inv, e);
	init_var_map(e->key);
	e->text->color_or_text = FALSE;
	creat_win(e);
	skybox(e);
	init_xpm_text(e);
	xpmt_secur(e);
}
