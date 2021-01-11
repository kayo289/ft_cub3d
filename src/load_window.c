/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkikuchi <kkikuchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 21:51:18 by kkikuchi          #+#    #+#             */
/*   Updated: 2021/01/06 21:55:34 by kkikuchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	f_min(int a, int b)
{
	if (a > b)
		return (b);
	else
		return (a);
}

static int	check_window_size(t_data *data)
{
	int		screen_width;
	int		screen_height;

	if (data->win.h <= 0 || data->win.w <= 0)
		return (0);
	mlx_get_screen_size(data->mlx, &screen_width, &screen_height);
	data->win.w = (int)f_min(data->win.w, screen_width);
	data->win.h = (int)f_min(data->win.h, screen_height);
	return (1);
}

void		load_win(t_data *data, char **str, int *i, char *line)
{
	(*i)++;
	if (!(str[1] && str[2]) || line[0] == ' ')
		error("load_win: Invalid element");
	if (str[3])
		error("Too many R argument");
	if (int_filter(str[1]))
		data->win.w = ft_atoi(str[1]);
	else
		error("Invalid R element");
	if (int_filter(str[2]))
		data->win.h = ft_atoi(str[2]);
	else
		error("Invalid R element");
	if (!(check_window_size(data)))
		error("load_win: Invalid window size");
}
