/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 13:37:29 by myang             #+#    #+#             */
/*   Updated: 2017/10/18 13:42:38 by myang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void	verif(char *line, t_env *e, int y, int *i)
{
	int	x;

	x = 0;
	while (x < e->map->s_x && line[*i] && line[*i] != '\n')
	{
		while (ft_isdigit(line[*i]) == 0)
			*i += 1;
		e->map->tabmap[y][x] = ft_atoi(&line[*i]);
		if (e->map->tabmap[y][x] == 3)
		{
			e->map->arrival[0] = x;
			e->map->arrival[1] = y;
		}
		x++;
		*i += 1;
	}
	*i += (line[*i] == '\n') ? 1 : 0;
}

void	init_var_map(t_key *key)
{
	key->mvmnt_f = FALSE;
	key->mvmnt_r = FALSE;
	key->mvmnt_l = FALSE;
	key->mvmnt_b = FALSE;
	key->rott_l = FALSE;
	key->rott_r = FALSE;
}

void	init_cam(t_env *e)
{
	e->merror = 0;
	e->dmg = FALSE;
	e->map->s_y = 0;
	e->map->s_x = 0;
	e->map->arrival[0] = 0;
	e->map->arrival[1] = 0;
	e->impact = 0;
	e->cam->dircam[0] = -1;
	e->cam->dircam[1] = 0;
	e->cam->dirwin[0] = 0;
	e->cam->dirwin[1] = -1;
	e->cam->vit = 0.25;
}

void	interface_mmap(t_env *e)
{
	if (!(e->text->xpm->minimap->i_img = mlx_new_image(e->mlx, 150, 150)))
		quit_exe(e, FALSE);
	if (!(e->text->xpm->minimap->bts =
		mlx_get_data_addr(e->text->xpm->minimap->i_img,
		&e->text->xpm->minimap->bpp, &e->text->xpm->minimap->size_line,
		&e->text->xpm->minimap->endian)))
		quit_exe(e, FALSE);
}

void	creat_win(t_env *e)
{
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, WIN_L, WIN_OH, "WOLF_3D");
	if (!(e->img->i_img = mlx_new_image(e->mlx, WIN_L, WIN_H)))
		quit_exe(e, FALSE);
	if (!(e->bts = mlx_get_data_addr(e->img->i_img, &e->img->bpp,
			&e->img->size_line, &e->img->endian)))
		quit_exe(e, FALSE);
}
