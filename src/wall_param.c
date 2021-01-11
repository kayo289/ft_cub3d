/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkikuchi <kkikuchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 12:40:44 by kkikuchi          #+#    #+#             */
/*   Updated: 2021/01/08 16:13:48 by kikuchika        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void				calc_sub_param(t_data *info, t_raycasting *rc, int x)
{
	rc->camera_x = 2 * x / (double)info->win.w - 1;
	rc->ray_dir_x = info->dir_x + info->plane_x * rc->camera_x;
	rc->ray_dir_y = info->dir_y + info->plane_y * rc->camera_x;
	rc->map_x = (int)info->pos_x;
	rc->map_y = (int)info->pos_y;
	rc->delta_dist_x = fabs(1 / rc->ray_dir_x);
	rc->delta_dist_y = fabs(1 / rc->ray_dir_y);
	rc->hit = 0;
}

void				calc_param(t_data *info, t_raycasting *rc, int x)
{
	calc_sub_param(info, rc, x);
	if (rc->ray_dir_x < 0)
	{
		rc->step_x = -1;
		rc->side_dist_x = (info->pos_x - rc->map_x) * rc->delta_dist_x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist_x = (rc->map_x + 1.0 - info->pos_x) * rc->delta_dist_x;
	}
	if (rc->ray_dir_y < 0)
	{
		rc->step_y = -1;
		rc->side_dist_y = (info->pos_y - rc->map_y) * rc->delta_dist_y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist_y = (rc->map_y + 1.0 - info->pos_y) * rc->delta_dist_y;
	}
}

void				set_side_param(t_data *info, t_raycasting *rc)
{
	if (rc->side == 0)
	{
		rc->prep_wall_dist = (rc->map_x - info->pos_x
						+ (1 - rc->step_x) / 2) / rc->ray_dir_x;
		rc->tex_num = (rc->ray_dir_x < 0) ? 0 : 2;
		rc->wall_x = info->pos_y + rc->prep_wall_dist * rc->ray_dir_y;
	}
	else
	{
		rc->prep_wall_dist = (rc->map_y - info->pos_y
						+ (1 - rc->step_y) / 2) / rc->ray_dir_y;
		rc->tex_num = (rc->ray_dir_y < 0) ? 3 : 1;
		rc->wall_x = info->pos_x + rc->prep_wall_dist * rc->ray_dir_x;
	}
}

void				calc_draw_param(t_data *info, t_raycasting *rc)
{
	set_side_param(info, rc);
	rc->line_height = (int)(info->win.h / rc->prep_wall_dist);
	rc->draw_start = -rc->line_height / 2 + info->win.h / 2;
	rc->draw_start = (rc->draw_start < 0) ? 0 : rc->draw_start;
	rc->draw_end = rc->line_height / 2 + info->win.h / 2;
	rc->draw_end = (rc->draw_end >= info->win.h) ?
			info->win.h - 1 : rc->draw_end;
	rc->wall_x -= floor((rc->wall_x));
	rc->tex_x = (int)(rc->wall_x * (double)info->tex[rc->tex_num].w);
	if ((rc->side == 1 && rc->ray_dir_y < 0) ||
		(rc->side == 0 && rc->ray_dir_x > 0))
		rc->tex_x = info->tex[rc->tex_num].w - rc->tex_x - 1;
	rc->step = 1.0 * info->tex[rc->tex_num].h / rc->line_height;
	rc->tex_pos = (rc->draw_start - info->win.h / 2
					+ rc->line_height / 2) * rc->step;
}
