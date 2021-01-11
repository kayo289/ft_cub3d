/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkikuchi <kkikuchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 05:46:11 by kkikuchi          #+#    #+#             */
/*   Updated: 2021/01/08 16:27:30 by kikuchika        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		draw(t_data *info)
{
	int		y;
	int		x;

	y = 0;
	while (y < info->win.h)
	{
		x = 0;
		while (x < info->win.w)
		{
			info->img.data[y * info->win.w + x] = info->buf[y][x];
			x++;
		}
		y++;
	}
}

void		draw_flor(t_data *info)
{
	int		y;
	int		x;

	y = 0;
	while (y < info->win.h)
	{
		x = 0;
		while (x < info->win.w)
		{
			if (y <= info->win.h / 2)
				info->buf[y][x] = info->color[1];
			else
				info->buf[y][x] = info->color[0];
			x++;
		}
		y++;
	}
}
