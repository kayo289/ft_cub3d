/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_casting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkikuchi <kkikuchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 22:52:30 by kkikuchi          #+#    #+#             */
/*   Updated: 2021/01/08 16:19:24 by kikuchika        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void				calc_sprite_param(t_data *info, t_raycasting *rc, int *i)
{
	info->sprite[*i].x = rc->map_x + 0.5;
	info->sprite[*i].y = rc->map_y + 0.5;
	info->sprite[*i].dist = ((info->pos_x - rc->map_x)
					* (info->pos_x - rc->map_x) + (info->pos_y - rc->map_y)
					* (info->pos_y - rc->map_y));
	(*i)++;
}

void				dda(t_data *info, t_raycasting *rc, int *i)
{
	while (rc->hit == 0)
	{
		if (rc->side_dist_x < rc->side_dist_y)
		{
			rc->side_dist_x += rc->delta_dist_x;
			rc->map_x += rc->step_x;
			rc->side = 0;
		}
		else
		{
			rc->side_dist_y += rc->delta_dist_y;
			rc->map_y += rc->step_y;
			rc->side = 1;
		}
		if (info->map[rc->map_x][rc->map_y] == '1')
			rc->hit = 1;
		if (info->map[rc->map_x][rc->map_y] == '2')
		{
			if (set(rc->map_x, rc->map_y, info) == 0)
				continue;
			calc_sprite_param(info, rc, i);
		}
	}
}

void				draw_wall(t_data *info, t_raycasting *rc, int x)
{
	int				y;

	calc_draw_param(info, rc);
	y = rc->draw_start;
	while (y < rc->draw_end)
	{
		rc->tex_y = (int)rc->tex_pos & (info->tex[rc->tex_num].h - 1);
		rc->tex_pos += rc->step;
		rc->color = info->tex[rc->tex_num].addr[info->tex[rc->tex_num].h
				* rc->tex_y + rc->tex_x];
		if (rc->side == 1)
			rc->color = (rc->color >> 1) & 8355711;
		info->buf[y][x] = rc->color;
		y++;
	}
}

void				wall_casting(t_data *info)
{
	t_raycasting	rc;
	int				i;
	int				x;

	i = 0;
	x = 0;
	while (i < TABLE_SIZE)
		info->hash_table[i++] = NULL;
	i = 0;
	info->sprite = (t_sprite *)malloc(sizeof(t_sprite) * info->sp_max);
	while (x < info->win.w)
	{
		calc_param(info, &rc, x);
		dda(info, &rc, &i);
		info->sp_n = i;
		draw_wall(info, &rc, x);
		info->z_buffer[x] = rc.prep_wall_dist;
		x++;
	}
	free_hash_table(info);
}
