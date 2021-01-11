/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkikuchi <kkikuchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 23:18:14 by kkikuchi          #+#    #+#             */
/*   Updated: 2021/01/11 21:55:49 by kikuchika        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void			free_hash_table(t_data *info)
{
	int			i;
	t_state		*start;
	t_state		*tmp;

	i = 0;
	while (i < TABLE_SIZE)
	{
		start = info->hash_table[i];
		while (start != NULL)
		{
			tmp = start->hash_link;
			free(start);
			start = tmp;
		}
		i++;
	}
}

void			free_str(char **map)
{
	int			i;

	i = 0;
	while (map[i] != NULL)
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map[i]);
	map[i] = NULL;
	free(map);
}

void			free_int(int **map)
{
	int			i;

	i = 0;
	while (map[i] != NULL)
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map[i]);
	map[i] = NULL;
	free(map);
}
