/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 17:48:01 by myang             #+#    #+#             */
/*   Updated: 2017/09/24 17:51:20 by myang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void	msg_error(void)
{
	ft_putendl("\nThe loaded map is currently wrong.");
	ft_putendl("Please follow those rules:");
	ft_putendl("\n-2: WALL WHICH MAKES DAMAGE.");
	ft_putendl("-1: BASIC WALL\n-0: PRACTIABLE AREA.");
	ft_putendl("\n-At least one PRACIABLE AREA (0).");
	ft_putendl("-All maps need to be surrounding by WALLs (1) or (2).");
	ft_putendl("For exemples:");
	ft_putendl("\t1 1 1\n\t1 0 1\n\t1 1 1\n");
	ft_putendl("\t1 1 1\n\t1 0 2\n\t1 2 2");
}

int		map_error(t_env *e, t_map *map)
{
	int	error;
	int	i;
	int	j;
	int	p_area;

	p_area = 0;
	error = 0;
	i = -1;
	j = 0;
	if (e->map->s_y > 1 && e->map->s_x - 1 > 1)
	{
		while (basic_i(&i, &j, e->map->s_y, e->map->s_x - 1) == 1)
		{
			error += (map->tabmap[j][0] <= 0 || map->tabmap[j][0] > 2) ? 1 : 0;
			error += (map->tabmap[j][map->s_x - 1] < 0 ||
					map->tabmap[j][map->s_x - 1] > 2) ? 1 : 0;
			error += (map->tabmap[0][i] <= 0 || map->tabmap[0][i] > 2) ? 1 : 0;
			error += (map->tabmap[map->s_y][i] < 0 &&
					map->tabmap[map->s_y][i] > 2) ? 1 : 0;
			error += (map->tabmap[j][i] > 2) ? 1 : 0;
			p_area += (map->tabmap[j][i] == 0) ? 1 : 0;
		}
	}
	return (error != 0 || p_area == 0) ? 0 : 1;
}

void	quit_error(t_env *e)
{
	msg_error();
	clear_struct_init(e);
	exit(EXIT_FAILURE);
}

void	quit_exe(t_env *e, int call)
{
	clear_struct_displayed(e, call);
	clear_struct_init(e);
	exit(EXIT_FAILURE);
}
