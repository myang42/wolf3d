/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 13:42:36 by myang             #+#    #+#             */
/*   Updated: 2017/09/24 17:47:31 by myang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

int	main(int ar, char **ac)
{
	t_env e;

	if (ar > 1 && ac[1] != NULL)
	{
		init_struct(&e);
		init_cam(&e);
		readfile(&e, ac[1]);
		if (map_error(&e, e.map) != 1)
			quit_error(&e);
		start_pos(&e, e.map) > 0 ? 0 : quit_error(&e);
		secur_init(&e);
		raycast_win_l(&e, e.ray);
		interface_mmap(&e);
		interface(&e);
		mlx_put_image_to_window(e.mlx, e.win, e.img->i_img, 0, 0);
		interface_txt(&e, e.text->xpm);
		music_bgm(&e);
		mlx_do_key_autorepeaton(e.mlx);
		mlx_hook(e.win, 2, 0, &keyfonc, &e);
		mlx_loop(e.mlx);
	}
	return (0);
}
