/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_form.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkikuchi <kkikuchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 22:23:41 by kkikuchi          #+#    #+#             */
/*   Updated: 2021/01/06 22:33:09 by kkikuchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void		setting_direct(t_data *info, char c)
{
	if (c == 'N' || c == 'S')
	{
		info->dir_x = -1.0;
		info->dir_y = 0.0;
		info->plane_x = 0.0;
		info->plane_y = 0.66;
		if (c == 'S')
		{
			info->dir_x *= -1;
			info->plane_y *= -1;
		}
	}
	else if (c == 'W' || c == 'E')
	{
		info->dir_x = 0.0;
		info->dir_y = -1.0;
		info->plane_x = -0.66;
		info->plane_y = 0.0;
		if (c == 'E')
		{
			info->dir_y *= -1;
			info->plane_x *= -1;
		}
	}
}

static void		get_start_pos(t_data *info, int x, int y, char c)
{
	info->map[x][y] = '0';
	if (info->pos_x != -42)
		error("get_start_pos:Invalid player cnt");
	info->pos_x = (double)x + 0.50;
	info->pos_y = (double)y + 0.50;
	setting_direct(info, c);
}

int				check_map_form(t_data *info)
{
	int			x;
	int			y;
	char		c;

	x = -1;
	while (++x < MAP_HEIGHT)
	{
		y = -1;
		while (++y < MAP_WIDTH)
		{
			c = info->map[x][y];
			if (('0' <= c && c <= '2') || c == 0)
			{
				if (c == '2')
					info->sp_max++;
			}
			else if (c == ' ')
				info->map[x][y] = '0';
			else if (ft_strchr("NESW", c))
				get_start_pos(info, x, y, c);
			else
				return (0);
		}
	}
	return (1);
}
