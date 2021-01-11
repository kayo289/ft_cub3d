/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkikuchi <kkikuchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 21:52:19 by kkikuchi          #+#    #+#             */
/*   Updated: 2021/01/11 21:10:31 by kikuchika        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void			kw(t_data *info)
{
	if (info->key.key_w)
	{
		if (info->map[(int)(info->pos_x + info->dir_x *
								info->move_speed)][(int)(info->pos_y)] == '0')
			info->pos_x += info->dir_x * info->move_speed;
		if (info->map[(int)(info->pos_x)][(int)(info->pos_y +
								info->dir_y * info->move_speed)] == '0')
			info->pos_y += info->dir_y * info->move_speed;
	}
	if (info->key.key_s)
	{
		if (info->map[(int)(info->pos_x - info->dir_x *
								info->move_speed)][(int)(info->pos_y)] == '0')
			info->pos_x -= info->dir_x * info->move_speed;
		if (info->map[(int)(info->pos_x)][(int)(info->pos_y -
								info->dir_y * info->move_speed)] == '0')
			info->pos_y -= info->dir_y * info->move_speed;
	}
}

void			ad(t_data *info)
{
	if (info->key.key_a)
	{
		if (info->map[(int)(info->pos_x - info->plane_x *
								info->move_speed)][(int)info->pos_y] == '0')
			info->pos_x -= info->plane_x * info->move_speed;
		if (info->map[(int)info->pos_x][(int)(info->pos_y -
								info->plane_y * info->move_speed)] == '0')
			info->pos_y -= info->plane_y * info->move_speed;
	}
	if (info->key.key_d)
	{
		if (info->map[(int)(info->pos_x + info->plane_x *
								info->move_speed)][(int)info->pos_y] == '0')
			info->pos_x += info->plane_x * info->move_speed;
		if (info->map[(int)(info->pos_x)][(int)(info->pos_y +
								info->plane_y * info->move_speed)] == '0')
			info->pos_y += info->plane_y * info->move_speed;
	}
}

int				key_press(int key, t_data *info)
{
	if (key == K_ESC)
		exit(0);
	else if (key == K_W || key == K_UP)
		info->key.key_w = 1;
	else if (key == LEFT)
		info->key.key_left = 1;
	else if (key == RIGHT)
		info->key.key_right = 1;
	else if (key == K_A)
		info->key.key_a = 1;
	else if (key == K_S || key == K_DOWN)
		info->key.key_s = 1;
	else if (key == K_D)
		info->key.key_d = 1;
	return (0);
}

int				key_release(int key, t_data *info)
{
	if (key == K_ESC)
		exit(0);
	else if (key == LEFT)
		info->key.key_left = 0;
	else if (key == RIGHT)
		info->key.key_right = 0;
	else if (key == K_W || key == K_UP)
		info->key.key_w = 0;
	else if (key == K_A)
		info->key.key_a = 0;
	else if (key == K_S || key == K_DOWN)
		info->key.key_s = 0;
	else if (key == K_D)
		info->key.key_d = 0;
	return (0);
}
