/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cubfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkikuchi <kkikuchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 20:28:54 by yohlee            #+#    #+#             */
/*   Updated: 2021/01/12 04:12:11 by kikuchika        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int				int_filter(char *s)
{
	int			i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

void			store_map(t_data *info, char **str,
			char *line, int *map_flag)
{
	static int	i;

	if (!ft_strncmp(str[0], "R", 2) && str[0][1] == 0)
		load_win(info, str, &i, line);
	else if (!ft_strncmp(str[0], "NO", 3) && str[0][2] == 0)
		info->tex[0].addr = load_img(info, str, 0, &i);
	else if (!ft_strncmp(str[0], "EA", 3) && str[0][2] == 0)
		info->tex[1].addr = load_img(info, str, 1, &i);
	else if (!ft_strncmp(str[0], "SO", 3) && str[0][2] == 0)
		info->tex[2].addr = load_img(info, str, 2, &i);
	else if (!ft_strncmp(str[0], "WE", 3) && str[0][2] == 0)
		info->tex[3].addr = load_img(info, str, 3, &i);
	else if (!ft_strncmp(str[0], "S", 1) && str[0][1] == 0)
		info->tex[4].addr = load_img(info, str, 4, &i);
	else if (!ft_strncmp(str[0], "F", 1) && str[0][1] == 0)
		info->color[0] = load_color(str, &i, line);
	else if (!ft_strncmp(str[0], "C", 1) && str[0][1] == 0)
		info->color[1] = load_color(str, &i, line);
	else if (ft_isdigit(*str[0]))
		load_map(info, line, &i, map_flag);
	else
		error("Invalid key");
}

static void		store(t_data *data, char *line, int *map_flag)
{
	char		**str;

	if (!(str = ft_split(line, ' ')))
		error("Not good format");
	if (*map_flag == 1 && (*line == '\0' || int_filter(str[0]) == 0))
		error("store:invalid map format");
	if (str[0] != NULL)
		store_map(data, str, line, map_flag);
	free_str(str);
}

void			read_cubfile(t_data *data, char *filename)
{
	int			fd;
	int			result;
	char		*line;
	size_t		len;
	static int	map_flag;

	len = ft_strlen(filename);
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		error("filename must end with cub");
	if ((fd = open(filename, O_RDONLY)) < 0)
		error("Can't open cub file");
	line = NULL;
	while (0 < (result = get_next_line(fd, &line)))
	{
		store(data, line, &map_flag);
		free(line);
		line = NULL;
	}
	free(line);
	if (map_flag == 0)
		error("read_cubfile:map nothing");
	close(fd);
}
