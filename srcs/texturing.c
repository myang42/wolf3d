/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 15:02:29 by myang             #+#    #+#             */
/*   Updated: 2017/09/24 18:09:14 by myang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

static char	*which_text(int walltextt)
{
	if (walltextt == 8)
		return ("./textures/text_arrival.xpm");
	if (walltextt == 1)
		return ("./textures/text_wall00.xpm");
	if (walltextt == 2)
		return ("./textures/text_wall01.xpm");
	if (walltextt == 3)
		return ("./textures/text_wall02.xpm");
	if (walltextt == 4)
		return ("./textures/text_wall03.xpm");
	if (walltextt == 6)
		return ("./textures/text_ceilling00.xpm");
	if (walltextt == 5)
		return ("./textures/text_ground00.xpm");
	if (walltextt == 7)
		return ("./textures/text_dmgwall.xpm");
	return (NULL);
}

t_img		*select_xpm(t_env *e, int walltextt)
{
	if (e->text->color_or_text == TRUE && e->cam->spewall == FALSE)
		e->text->walltextt = e->cam->correct + 1;
	else if (e->text->color_or_text == TRUE && e->cam->spewall >= 1)
	{
		if (e->cam->spewall == 1)
			walltextt = 7;
		else
			walltextt = 8;
	}
	if (walltextt == 8)
		return (e->text->xpm->xpm_t0);
	if (walltextt == 1)
		return (e->text->xpm->xpm_t1);
	if (walltextt == 2)
		return (e->text->xpm->xpm_t2);
	if (walltextt == 3)
		return (e->text->xpm->xpm_t3);
	if (walltextt == 4)
		return (e->text->xpm->xpm_t4);
	if (walltextt == 5)
		return (e->text->xpm->xpm_t5);
	if (walltextt == 6)
		return (e->text->xpm->xpm_t6);
	else
		return (e->text->xpm->xpm_t7);
}

void		init_xpm_text(t_env *e)
{
	if (!(e->text->xpm->xpm_t0 = (t_img*)malloc(sizeof(t_img))))
		quit_exe(e, FALSE);
	if (!(e->text->xpm->xpm_t1 = (t_img*)malloc(sizeof(t_img))))
		quit_exe(e, FALSE);
	if (!(e->text->xpm->xpm_t2 = (t_img*)malloc(sizeof(t_img))))
		quit_exe(e, FALSE);
	if (!(e->text->xpm->xpm_t3 = (t_img*)malloc(sizeof(t_img))))
		quit_exe(e, FALSE);
	if (!(e->text->xpm->xpm_t4 = (t_img*)malloc(sizeof(t_img))))
		quit_exe(e, FALSE);
	if (!(e->text->xpm->xpm_t5 = (t_img*)malloc(sizeof(t_img))))
		quit_exe(e, FALSE);
	if (!(e->text->xpm->xpm_t6 = (t_img*)malloc(sizeof(t_img))))
		quit_exe(e, FALSE);
	if (!(e->text->xpm->xpm_t7 = (t_img*)malloc(sizeof(t_img))))
		quit_exe(e, FALSE);
}

void		walltexturing(t_env *e, int wallnbr, t_img *xpmt)
{
	char	*wallname;

	wallname = ft_strdup(which_text(wallnbr));
	if (wallname == NULL)
		quit_exe(e, FALSE);
	if (!(xpmt->i_img = mlx_xpm_file_to_image(e->mlx, wallname,
			&xpmt->textx, &xpmt->texty)))
		quit_exe(e, FALSE);
	if (!(xpmt->bts = mlx_get_data_addr(xpmt->i_img, &xpmt->bpp,
			&xpmt->size_line, &xpmt->endian)))
		quit_exe(e, FALSE);
	ft_strdel(&wallname);
}
