/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkikuchi <kkikuchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 22:20:01 by kkikuchi          #+#    #+#             */
/*   Updated: 2021/01/08 16:25:57 by kikuchika        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_map(t_data *info)
{
	int	i;

	i = 0;
	while (i < 5 && info->tex[i].addr)
		i++;
	if (i != 5)
		error("Not a normal amount of keys");
	if (info->win.w == -42)
		error("not good win");
	if (!check_map_form(info))
		error("Invalid map format");
	if (info->pos_x == -42)
		error("No player");
	check_map_closed(info);
	if (info->color[0] == UINT32_MAX || info->color[1] == UINT32_MAX)
		error("not enough color data");
}
