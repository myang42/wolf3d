/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dmg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 18:05:21 by myang             #+#    #+#             */
/*   Updated: 2017/09/23 18:06:41 by myang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void	dmg_anim(t_env *e, double lastx, double lasty, t_cam *cam)
{
	e->cam->poscam[0] = lastx - cam->varx * cam->vit;
	e->cam->poscam[1] = lasty - cam->vary * cam->vit;
	e->inv->pv->nbr -= 1;
	clear_all(e, FALSE);
	if (e->inv->pv->nbr <= 0)
	{
		sprite_data(e->text->xpm->gameover, "./textures/GameOver.xpm", e);
		(!(mlx_put_image_to_window(e->mlx, e->win,
				e->text->xpm->gameover->i_img, 0, 0))) ? quit_exe(e, TRUE) : 0;
		mlx_string_put(e->mlx, e->win, 225, WIN_OH / 2 + 190, WHITE,
				"Press ESC for QUIT");
	}
	else
	{
		raycast_win_l(e, e->ray);
		mlx_put_image_to_window(e->mlx, e->win, e->img->i_img, 0, 0);
		interface_txt(e, e->text->xpm);
	}
}

void	farrival(t_env *e)
{
	e->inv->pv->nbr = -1;
	clear_all(e, FALSE);
	sprite_data(e->text->xpm->arrival, "./textures/arrival.xpm", e);
	(!(mlx_put_image_to_window(e->mlx, e->win,
			e->text->xpm->arrival->i_img, 0, 0))) ? quit_exe(e, TRUE) : 0;
	mlx_string_put(e->mlx, e->win, 225, WIN_OH / 2 + 190, WHITE,
			"Press ESC for QUIT");
}
