/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkikuchi <kkikuchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 22:50:55 by kkikuchi          #+#    #+#             */
/*   Updated: 2021/01/08 16:28:12 by kikuchika        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void			sort_order(t_data *info)
{
	t_sprite	tmp;
	int			i;
	int			j;

	i = 0;
	while (i < info->sp_n)
	{
		j = 0;
		while (j < info->sp_n - 1)
		{
			if (info->sprite[j].dist < info->sprite[j + 1].dist)
			{
				tmp = info->sprite[j];
				info->sprite[j] = info->sprite[j + 1];
				info->sprite[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}
