/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_closed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkikuchi <kkikuchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 22:04:59 by kkikuchi          #+#    #+#             */
/*   Updated: 2021/01/11 21:54:24 by kikuchika        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void		dfs(int **check_map,
				int x, int y)
{
	if (x < 0 || y < 0 || x >= MAP_WIDTH || y >= MAP_HEIGHT)
		error("map not closed");
	if (check_map[x][y] == 1)
		return ;
	check_map[x][y] = 1;
	dfs(check_map, x - 1, y);
	dfs(check_map, x + 1, y);
	dfs(check_map, x, y - 1);
	dfs(check_map, x, y + 1);
}

void			check_map_closed(t_data *data)
{
	int			**check_map;
	int			i;
	int			j;

	i = 0;
	if (!(check_map = (int**)malloc((sizeof(int*) * (MAP_HEIGHT + 1)))))
		error("malloc fail");
	while (i < MAP_HEIGHT)
		check_map[i++] = (int*)malloc(sizeof(int) * MAP_WIDTH);
	check_map[i] = NULL;
	i = 0;
	while (i < MAP_HEIGHT)
	{
		j = -1;
		while (++j < MAP_WIDTH)
		{
			if (data->map[i][j] == '1')
				check_map[i][j] = 1;
			else
				check_map[i][j] = 0;
		}
		i++;
	}
	dfs(check_map, (int)data->pos_x, (int)data->pos_y);
	free_int(check_map);
}
