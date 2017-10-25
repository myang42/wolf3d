/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 17:48:01 by myang             #+#    #+#             */
/*   Updated: 2017/10/23 16:14:54 by myang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void	msg_error(void)
{
	ft_putendl_fd("\nThe loaded map is currently wrong.", 2);
	ft_putendl_fd("Please follow thoses rules:", 2);
	ft_putendl_fd("\n-3: WALL WHICH IS THE ARRIVAL. (optional)", 2);
	ft_putendl_fd("-2: WALL WHICH MAKES DAMAGE. (optional)", 2);
	ft_putendl_fd("-1: BASIC WALL\n-0: PRACTICABLE AREA.", 2);
	ft_putendl_fd("\n-At least one PRACIABLE AREA (0).", 2);
	ft_putendl_fd("-All maps need to be surrounding by WALLs (1, 2 or 3).", 2);
	ft_putendl_fd("\nFor exemples:", 2);
	ft_putendl_fd("\n\t1 1 1\n\t1 0 3\n\t1 1 1\n", 2);
	ft_putendl_fd("\t1 1 2 2 1\n\t1 0 3 0 2\n\t1 0 0 0 1\n\t1 1 1 1 1\n", 2);
}

int		txt_error(char *tmp)
{
	size_t	index;

	index = 0;
	while (index < ft_strlen(tmp))
	{
		if ((tmp[index] != '\n' && tmp[index] != ' ' && tmp[index] != '\0') &&
		ft_isdigit(tmp[index]) == 0)
			return (1);
		index++;
	}
	return (0);
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
			error += (map->tabmap[j][0] <= 0 || map->tabmap[j][0] > 3) ? 1 : 0;
			error += (map->tabmap[j][map->s_x - 1] <= 0 ||
					map->tabmap[j][map->s_x - 1] > 3) ? 1 : 0;
			error += (map->tabmap[0][i] <= 0 || map->tabmap[0][i] > 3) ? 1 : 0;
			error += (map->tabmap[map->s_y][i] < 0 &&
					map->tabmap[map->s_y][i] > 3) ? 1 : 0;
			error += (map->tabmap[j][i] > 3) ? 1 : 0;
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
