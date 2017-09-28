/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 18:05:22 by myang             #+#    #+#             */
/*   Updated: 2017/09/24 18:07:57 by myang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void		sprite_data(t_img *xpm_selected, char *xpm_name, t_env *e)
{
	xpm_selected->i_img = mlx_xpm_file_to_image(e->mlx, xpm_name,
			&xpm_selected->textx, &xpm_selected->texty);
	xpm_selected->bts = mlx_get_data_addr(xpm_selected->i_img,
			&xpm_selected->bpp, &xpm_selected->size_line,
			&xpm_selected->endian);
}

static char	*heart_val(int cmpt, t_inv *pv)
{
	if (pv->nbr < 4 * cmpt)
	{
		if (pv->nbr == (4 * cmpt - 1))
			return ("./textures/pv_3.XPM");
		else if (pv->nbr == (4 * cmpt - 2))
			return ("./textures/pv_2.XPM");
		else if (pv->nbr == (4 * cmpt - 3))
			return ("./textures/pv_1.XPM");
		else
			return ("./textures/pv_0.XPM");
	}
	else
		return ("./textures/pv_4.XPM");
}

static void	weapon_select(int select, t_env *e)
{
	char	*weapon_sprite;
	char	*weapon_wicon;
	t_xpm	*xpmt;

	xpmt = e->text->xpm;
	if (select == 0)
	{
		weapon_sprite = "./textures/chainsaw.xpm";
		weapon_wicon = "./textures/icon_BFG9000.xpm";
	}
	else
	{
		weapon_sprite = "./textures/BFG9000.xpm";
		weapon_wicon = "./textures/icon_chainsaw.xpm";
	}
	sprite_data(xpmt->xpm_weapon, weapon_sprite, e);
	sprite_data(xpmt->xpm_wicon, weapon_wicon, e);
	mlx_put_image_to_window(e->mlx, e->win, xpmt->xpm_wicon->i_img, 515, 390);
	mlx_put_image_to_window(e->mlx, e->win, xpmt->xpm_weapon->i_img, 175, 210);
}

void		interface_txt(t_env *e, t_xpm *xpm)
{
	mlx_put_image_to_window(e->mlx, e->win, xpm->window_1->i_img,
			0, WIN_H);
	sprite_data(xpm->xpm_pv1, heart_val(1, e->inv->pv), e);
	sprite_data(xpm->xpm_pv2, heart_val(2, e->inv->pv), e);
	sprite_data(xpm->xpm_pv3, heart_val(3, e->inv->pv), e);
	mlx_put_image_to_window(e->mlx, e->win, xpm->xpm_pv1->i_img, 10, 10);
	mlx_put_image_to_window(e->mlx, e->win, xpm->xpm_pv2->i_img, 60, 10);
	mlx_put_image_to_window(e->mlx, e->win, xpm->xpm_pv3->i_img, 110, 10);
	mlx_string_put(e->mlx, e->win,
			600 - ft_strlen(ft_itoa(e->inv->tokken->nbr)) * 10, 20, 0,
			ft_itoa(e->inv->tokken->nbr));
	mlx_string_put(e->mlx, e->win, 70, 440, WHITE, "x");
	mlx_string_put(e->mlx, e->win, 80, 440, WHITE, ft_itoa(e->inv->ammo->nbr));
	weapon_select(e->inv->weapon->nbr, e);
	draw_mmap(e->cam, e, e->map);
	mlx_put_image_to_window(e->mlx, e->win,
			xpm->minimap->i_img, 5, WIN_OH - 155);
}

void		interface(t_env *e)
{
	t_img	*interface;

	interface = e->text->xpm->window_1;
	interface->i_img = mlx_xpm_file_to_image(e->mlx,
			"./textures/interface_templ.xpm", &interface->textx,
			&interface->texty);
	interface->bts = mlx_get_data_addr(interface->i_img, &interface->bpp,
			&interface->size_line, &interface->endian);
}
