/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyfcnt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 12:46:14 by myang             #+#    #+#             */
/*   Updated: 2017/10/25 15:47:56 by myang            ###   ########.fr       */
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
	if ((mvmnt == TRUE) && (int)e->cam->poscam[0] == e->map->arrival[0] &&
	(int)e->cam->poscam[1] == e->map->arrival[1])
		farrival(e);
	else
	{
		clear_all(e, FALSE);
		//
		if (e->text->color_or_text == TRUE)
			printf("..\n");
		//
		raycast_win_l(e, e->ray);
		if (e->text->color_or_text == TRUE)
			printf(".!.\n");
		mlx_put_image_to_window(e->mlx, e->win, e->img->i_img, 0, 0);
		interface_txt(e, e->text->xpm);
		if (e->text->color_or_text == TRUE)
			printf(".?.\n");
		if ((mvmnt == TRUE) && e->dmg == TRUE)
			dmg_anim(e, lastpos[0], lastpos[1], e->cam);
		e->dmg = FALSE;
	}
}

int			red_cross(int key, t_env *e)
{
	(void)key;
	(void)*e;
	system("killall afplay");
	exit(0);
	return (0);
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
