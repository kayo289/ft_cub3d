/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkikuchi <kkikuchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 21:59:50 by kkikuchi          #+#    #+#             */
/*   Updated: 2021/01/08 16:32:34 by kikuchika        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void			load_map(t_data *data, char *line, int *j, int *map_flag)
{
	static int	i;
	int			w;

	if (*j != 8)
		error("Incorrect key quantity");
	if (*map_flag == 0)
		*map_flag = 1;
	if (i >= MAP_WIDTH)
		error("hegit of map is overflow");
	w = ft_strlcpy(data->map[i++], line, MAP_WIDTH);
	if (w >= MAP_WIDTH)
		error("width of map is overflow");
}
