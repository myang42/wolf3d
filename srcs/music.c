/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 17:54:53 by myang             #+#    #+#             */
/*   Updated: 2017/09/24 17:55:09 by myang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void	music_select(t_music *bgm)
{
	system("killall afplay");
	if (bgm->selected == 0)
		system("afplay ./musics/music1.wav -v 0.3 &");
	else if (bgm->selected == 1)
		system("afplay ./musics/music2.wav -v 0.3 &");
	else
		system("afplay ./musics/music3.wav -v 0.3 &");
}

void	music_bgm(t_env *e)
{
	if (!(e->music = (t_music*)malloc(sizeof(t_music))))
		exit(EXIT_FAILURE);
	e->music->selected = 0;
	system("afplay ./musics/music3.wav -v 0 &");
	system("afplay ./musics/music2.wav -v 0 &");
	system("afplay ./musics/music1.wav -v 0 &");
	music_select(e->music);
}
