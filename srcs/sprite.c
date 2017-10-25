/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 18:05:22 by myang             #+#    #+#             */
/*   Updated: 2017/10/23 16:13:41 by myang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void		sprite_data(t_img *xpm_selected, char *xpm_name, t_env *e)
{
	if (!(xpm_selected->i_img = mlx_xpm_file_to_image(e->mlx, xpm_name,
		&xpm_selected->textx, &xpm_selected->texty)))
		quit_exe(e, FALSE);
	if (!(xpm_selected->bts = mlx_get_data_addr(xpm_selected->i_img,
		&xpm_selected->bpp, &xpm_selected->size_line,
		&xpm_selected->endian)))
		quit_exe(e, FALSE);
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
		weapon_wicon = "./textures/icon_chainsaw.xpm";
	}
	else
	{
		weapon_sprite = "./textures/BFG9000.xpm";
		weapon_wicon = "./textures/icon_BFG9000.xpm";
	}
	sprite_data(xpmt->xpm_weapon, weapon_sprite, e);
	sprite_data(xpmt->xpm_wicon, weapon_wicon, e);
	mlx_put_image_to_window(e->mlx, e->win, xpmt->xpm_wicon->i_img, 515, 390);
	mlx_put_image_to_window(e->mlx, e->win, xpmt->xpm_weapon->i_img, 175, 210);
}

void		interface_txt(t_env *e, t_xpm *xpm)
{
	int		size;
	char	*nbr_char;
	char	*nbr_ammo;

	nbr_ammo = ft_itoa(e->inv->ammo->nbr);
	nbr_char = ft_itoa(e->inv->tokken->nbr);
	size = 600 - (1 + ft_strlen(nbr_char)) * 10;
	mlx_put_image_to_window(e->mlx, e->win, xpm->window_1->i_img,
			0, WIN_H - 60);
	sprite_data(xpm->xpm_pv1, heart_val(1, e->inv->pv), e);
	sprite_data(xpm->xpm_pv2, heart_val(2, e->inv->pv), e);
	sprite_data(xpm->xpm_pv3, heart_val(3, e->inv->pv), e);
	mlx_put_image_to_window(e->mlx, e->win, xpm->xpm_pv1->i_img, 240, 405);
	mlx_put_image_to_window(e->mlx, e->win, xpm->xpm_pv2->i_img, 300, 405);
	mlx_put_image_to_window(e->mlx, e->win, xpm->xpm_pv3->i_img, 360, 405);
	mlx_string_put(e->mlx, e->win, size, 20, 0, nbr_char);
	mlx_string_put(e->mlx, e->win, 70, 440, WHITE, "x");
	mlx_string_put(e->mlx, e->win, 80, 440, WHITE, nbr_ammo);
	weapon_select(e->inv->weapon->nbr, e);
	draw_mmap(e->cam, e, e->map);
	mlx_put_image_to_window(e->mlx, e->win,
			xpm->minimap->i_img, 5, WIN_OH - 155);
	ft_strdel(&nbr_char);
	ft_strdel(&nbr_ammo);
}

void		interface(t_env *e)
{
	t_img	*interface;

	interface = e->text->xpm->window_1;
	if (!(interface->i_img = mlx_xpm_file_to_image(e->mlx,
			"./textures/interfaceWOLF.xpm", &interface->textx,
			&interface->texty)))
		quit_exe(e, FALSE);
	if (!(interface->bts = mlx_get_data_addr(interface->i_img, &interface->bpp,
			&interface->size_line, &interface->endian)))
		quit_exe(e, FALSE);
}
