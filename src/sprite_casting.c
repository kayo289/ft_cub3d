/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_casting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkikuchi <kkikuchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:25:48 by kkikuchi          #+#    #+#             */
/*   Updated: 2021/01/08 18:21:52 by kikuchika        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void				sort_order(t_data *info)
{
	t_sprite		tmp;
	int				i;
	int				j;

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

void				calc_sp_param(t_sprite_draw *sp, t_data *info, int idx)
{
	sp->x = info->sprite[idx].x - info->pos_x;
	sp->y = info->sprite[idx].y - info->pos_y;
	sp->inv_det = 1.0 / (info->plane_x * info->dir_y -
						info->dir_x * info->plane_y);
	sp->trans_form_x = sp->inv_det * (info->dir_y *
										sp->x - info->dir_x * sp->y);
	sp->trans_form_y = sp->inv_det * (-info->plane_y * sp->x +
					info->plane_x * sp->y);
	sp->screen_x = (int)((info->win.w / 2) * (1 +
					sp->trans_form_x / sp->trans_form_y));
	sp->v_move_screen = (int)(0.0 / sp->trans_form_y);
	sp->height = (int)fabs((info->win.h / sp->trans_form_y) / 1);
	sp->draw_start_y = -sp->height / 2 + info->win.h / 2 + sp->v_move_screen;
	sp->draw_start_y = (sp->draw_start_y < 0) ? 0 : sp->draw_start_y;
	sp->draw_end_y = sp->height / 2 + info->win.h / 2 + sp->v_move_screen;
	sp->draw_end_y = (sp->draw_end_y >= info->win.h) ?
			info->win.h - 1 : sp->draw_end_y;
	sp->width = (int)fabs((info->win.h / sp->trans_form_y) / 1);
	sp->draw_start_x = -sp->width / 2 + sp->screen_x;
	sp->draw_start_x = (sp->draw_start_x < 0) ? 0 : sp->draw_start_x;
	sp->draw_end_x = sp->width / 2 + sp->screen_x;
	sp->draw_end_x = (sp->draw_end_x >= info->win.w) ?
			info->win.w - 1 : sp->draw_end_x;
}

void				draw_casting(t_sprite_draw *sp, int *stripe, t_data *info)
{
	int				y;
	int				d;

	*stripe = sp->draw_start_x;
	while (*stripe < sp->draw_end_x)
	{
		sp->tex_x = (int)((256 * (*stripe - (-sp->width / 2 +
							sp->screen_x)) * info->tex[4].w / sp->width) / 256);
		if (sp->trans_form_y > 0 && *stripe > 0 && *stripe < info->win.w
						&& sp->trans_form_y < info->z_buffer[*stripe])
		{
			y = sp->draw_start_y - 1;
			while (++y < sp->draw_end_y)
			{
				d = (y - sp->v_move_screen) * 256 - info->win.h * 128 +
						sp->height * 128;
				sp->tex_y = ((d * info->tex[4].h) / sp->height) / 256;
				sp->color = info->tex[4].addr[info->tex[4].w *
						sp->tex_y + sp->tex_x];
				if ((sp->color & 0x00FFFFFF) != 0)
					info->buf[y][*stripe] = sp->color;
			}
		}
		(*stripe)++;
	}
}

void				sprite_casting(t_data *info)
{
	int				stripe;
	int				i;
	t_sprite_draw	sp;

	sort_order(info);
	i = 0;
	while (i < info->sp_n)
	{
		calc_sp_param(&sp, info, i);
		draw_casting(&sp, &stripe, info);
		i++;
	}
	free(info->sprite);
}
