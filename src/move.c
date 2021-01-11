/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkikuchi <kkikuchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 21:55:40 by kkikuchi          #+#    #+#             */
/*   Updated: 2021/01/08 16:30:16 by kikuchika        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void			right(t_data *info)
{
	double		old_dir_x;
	double		old_plane_x;

	old_dir_x = info->dir_x;
	info->dir_x = info->dir_x * cos(-info->rot_speed) -
			info->dir_y * sin(-info->rot_speed);
	info->dir_y = old_dir_x * sin(-info->rot_speed) +
			info->dir_y * cos(-info->rot_speed);
	old_plane_x = info->plane_x;
	info->plane_x = info->plane_x * cos(-info->rot_speed)
			- info->plane_y * sin(-info->rot_speed);
	info->plane_y = old_plane_x * sin(-info->rot_speed)
			+ info->plane_y * cos(-info->rot_speed);
}

void			left(t_data *info)
{
	double		old_dir_x;
	double		old_plane_x;

	old_dir_x = info->dir_x;
	info->dir_x = info->dir_x * cos(info->rot_speed) -
			info->dir_y * sin(info->rot_speed);
	info->dir_y = old_dir_x * sin(info->rot_speed) +
			info->dir_y * cos(info->rot_speed);
	old_plane_x = info->plane_x;
	info->plane_x = info->plane_x * cos(info->rot_speed) -
			info->plane_y * sin(info->rot_speed);
	info->plane_y = old_plane_x * sin(info->rot_speed) +
			info->plane_y * cos(info->rot_speed);
}

void			key_update(t_data *info)
{
	kw(info);
	ad(info);
	if (info->key.key_right)
		right(info);
	if (info->key.key_left)
		left(info);
	if (info->key.key_esc)
		exit(0);
}
