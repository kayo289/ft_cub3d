/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkikuchi <kkikuchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 21:24:46 by kkikuchi          #+#    #+#             */
/*   Updated: 2021/01/12 04:17:40 by kikuchika        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void		sub_load_image(int *addr, t_img *img)
{
	int			x;
	int			y;

	y = 0;
	while (y < img->img_h)
	{
		x = 0;
		while (x < img->img_w)
		{
			addr[img->img_w * y + x] = img->data[img->img_w * y + x];
			x++;
		}
		y++;
	}
}

int				*load_img(t_data *info, char **str, int j, int *i)
{
	t_img		img;
	int			*addr;

	(*i)++;
	if (str[2] || !str[1])
		error("load_img:invalid element");
	if (open(str[1], O_RDONLY) < 0)
		error("load_img: invalid path");
	if (ft_strncmp(str[1] + ft_strlen(str[1]) - 4, ".xpm", 4) != 0)
		error("filename must end with cub");
	img.img = mlx_xpm_file_to_image(info->mlx, str[1], &img.img_w, &img.img_h);
	img.data = (int *)mlx_get_data_addr(img.img, &img.bpp,
										&img.size_l, &img.endian);
	if (!(addr = (int *)malloc(sizeof(int) * (img.img_w * img.img_h))))
		exit(1);
	info->tex[j].w = img.img_w;
	info->tex[j].h = img.img_h;
	sub_load_image(addr, &img);
	mlx_destroy_image(info->mlx, img.img);
	return (addr);
}
