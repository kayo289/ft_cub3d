/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkikuchi <kkikuchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 21:37:34 by kkikuchi          #+#    #+#             */
/*   Updated: 2021/01/08 16:33:31 by kikuchika        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int			count_connma(char *str)
{
	int				i;
	int				cnt;

	i = 0;
	cnt = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ',')
			cnt++;
		i++;
	}
	return (cnt);
}

uint32_t			load_color(char **str, int *i, char *line)
{
	char			**color_s;
	uint32_t		color[3];

	(*i)++;
	if (str[1] == NULL || str[2] != NULL || line[0] == ' ')
		error("load_color:invalid element");
	color_s = ft_split(str[1], ',');
	if (count_connma(str[1]) != 2)
		error("in Color: invalid element");
	if (!(color_s[0] != NULL && color_s[1] != NULL && color_s[2] != NULL))
		error("in Color: not enough egb");
	if (color_s[3] != NULL || str[2] != NULL)
		error("in Color:too many element");
	if (!(int_filter(color_s[0]) && int_filter(color_s[1])
							&& int_filter(color_s[2])))
		error("color element is not integer");
	color[0] = ft_atoi(color_s[0]);
	color[1] = ft_atoi(color_s[1]);
	color[2] = ft_atoi(color_s[2]);
	free_str(color_s);
	if (color[0] > 255 || color[1] > 255 || color[2] > 255)
		error("Invalid RGB value");
	return ((color[0] << 16) + (color[1] << 8) + color[2]);
}
