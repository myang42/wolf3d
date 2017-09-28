/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyfcnt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 12:46:14 by myang             #+#    #+#             */
/*   Updated: 2017/09/24 16:40:45 by myang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

static void	trz(t_env *e, t_key *key)
{
	double	lastpos[2];
	int		mvmnt;

	mvmnt = FALSE;
	lastpos[0] = e->cam->poscam[0];
	lastpos[1] = e->cam->poscam[1];
	if (key->rott_r == TRUE || key->rott_l == TRUE)
		mvmnt = mvmnt_camrott(e);
	if (key->mvmnt_f == TRUE || key->mvmnt_b == TRUE ||
			key->mvmnt_r == TRUE || key->mvmnt_l == TRUE)
		mvmnt = mvmnt_camdir(e, e->cam, e->cam->poscam[0], e->cam->poscam[1]);
	clear_all(e, FALSE);
	raycast_win_l(e, e->ray);
	mlx_put_image_to_window(e->mlx, e->win, e->img->i_img, 0, 0);
	interface_txt(e, e->text->xpm);
	if ((mvmnt == TRUE) && e->dmg == TRUE)
		dmg_anim(e, lastpos[0], lastpos[1], e->cam);
	e->dmg = FALSE;
}

static void	keyfonc_isalive(int key, t_env *e)
{
	if (key == KEY_1)
		e->inv->weapon->nbr = 1;
	else if (key == KEY_2)
		e->inv->weapon->nbr = 0;
	key_pressed(e, key);
	if (key == KEY_T && e->text->color_or_text != TRUE)
		e->text->color_or_text = TRUE;
	else if (key == KEY_T && e->text->color_or_text != FALSE)
		e->text->color_or_text = FALSE;
	if (key == KEY_C)
		e->text->color_or_text = (e->text->color_or_text != 2) ? 2 : 0;
	trz(e, e->key);
	if (key == KEY_M)
	{
		e->music->selected += (e->music->selected < 2) ? 1 : -2;
		music_select(e->music);
	}
	init_var_map(e->key);
}

int			keyfonc(int key, t_env *e)
{
	if (key == KEY_ESC)
	{
		system("killall afplay");
		(e->inv->pv->nbr <= 0) ? quit_exe(e, FALSE) : quit_exe(e, TRUE);
	}
	if (e->inv->pv->nbr > 0)
		keyfonc_isalive(key, e);
	return (1);
}
