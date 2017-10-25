/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/30 13:42:19 by myang             #+#    #+#             */
/*   Updated: 2017/10/24 17:25:50 by myang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void		creat_dint(char *line, int nbr_y, t_env *e, t_map *map)
{
	int	y;
	int	i;
	int	x;

	i = 0;
	y = 0;
	while (line[i] != '\n' && line[i] != '\0')
	{
		e->map->s_x += (ft_isdigit(line[i])) ? 1 : 0;
		i++;
	}
	x = e->map->s_x;
	i = 0;
	if (!(map->tabmap = (int**)malloc(sizeof(int*) * (nbr_y + 1))))
		quit_error(e);
	while (y <= nbr_y)
	{
		if (!(map->tabmap[y] = (int*)malloc(sizeof(int) * (x + 1))))
			quit_error(e);
		verif(line, e, y, &i);
		y += 1;
	}
}

void		sy_size(char *line, t_env *e)
{
	int	i;
	int	size;

	size = 0;
	i = 0;
	while (line[i++] != '\0')
		size += (line[i] == '\n') ? 1 : 0;
	if (ft_findme(line, '\n') == -1 && line[0] != '\0')
		size = 1;
	e->map->s_y = size;
}

void		dup_or_join(t_env *e, char *book, char **l, char **line)
{
	if (*l == NULL)
	{
		if (book[0] != '\0')
			*line = ft_strdup(book);
		else
			quit_error(e);
	}
	else
	{
		*line = ft_strjoin(*l, book);
		ft_strdel(l);
	}
}

static void	to_gnl(t_env *e, const int fd, char *line, t_map *map)
{
	int		rd;
	char	book[BUFF_SIZE_GNL + 1];
	char	*l;

	ft_bzero(book, BUFF_SIZE_GNL);
	l = NULL;
	while ((rd = read(fd, book, BUFF_SIZE_GNL)) > 0)
	{
		book[rd] = '\0';
		if ((e->merror = txt_error(book)) == 1)
			quit_error(e);
		dup_or_join(e, book, &l, &line);
		l = ft_strdup(line);
		ft_strdel(&line);
		if (rd < BUFF_SIZE_GNL && ft_findme(book, '\0') != -1)
			break ;
		ft_bzero(book, BUFF_SIZE_GNL);
	}
	(rd == 0 && l == NULL) ? quit_error(e) : 0;
	line = ft_strtrim(l);
	sy_size(line, e);
	ft_strdel(&l);
	creat_dint(line, e->map->s_y, e, map);
	ft_strdel(&line);
}

void		readfile(t_env *e, char *ac)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open(ac, O_RDONLY);
	(fd > 0) ? to_gnl(e, fd, line, e->map) : quit_error(e);
	if (line)
	{
		free(line);
		line = NULL;
	}
	close(fd);
}
