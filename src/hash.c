/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkikuchi <kkikuchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 05:40:26 by kkikuchi          #+#    #+#             */
/*   Updated: 2021/01/08 16:36:36 by kikuchika        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int			hash(int x, int y)
{
	int				tmp;
	int				hash_value;

	tmp = y;
	hash_value = x;
	while (tmp)
	{
		tmp /= 10;
		hash_value *= 10;
		hash_value %= TABLE_SIZE;
	}
	hash_value += y;
	hash_value %= TABLE_SIZE;
	return (hash_value);
}

static t_state		*create_lst(int x, int y, t_state *link)
{
	t_state			*next;

	next = (t_state *)malloc(sizeof(t_state) * 1);
	next->x = x;
	next->y = y;
	next->hash_link = link;
	return (next);
}

int					set(int x, int y, t_data *info)
{
	int				hash_value;
	t_state			*top;
	t_state			*state;

	hash_value = hash(x, y);
	top = info->hash_table[hash_value];
	while (top != NULL)
	{
		if (top->x == x && top->y == y)
			return (0);
		top = top->hash_link;
	}
	state = create_lst(x, y, info->hash_table[hash_value]);
	info->hash_table[hash_value] = state;
	return (1);
}
