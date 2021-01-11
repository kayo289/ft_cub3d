/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkikuchi <kkikuchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 22:44:28 by kkikuchi          #+#    #+#             */
/*   Updated: 2021/01/08 18:19:15 by kikuchika        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void		build_header(t_data *data, char *bmp_header, uint32_t n_pixel)
{
	int			i;
	t_header	h;

	i = 0;
	h.file_size = n_pixel + 54;
	h.offset = 54;
	h.header_size = 40;
	h.planes = 1;
	h.bpp = 32;
	ft_memcpy(&bmp_header[i], "BM", 2);
	ft_memcpy(&bmp_header[i += 2], &h.file_size, 4);
	ft_memset(&bmp_header[i += 4], 0, 4);
	ft_memcpy(&bmp_header[i += 4], &h.offset, 4);
	ft_memcpy(&bmp_header[i += 4], &h.header_size, 4);
	ft_memcpy(&bmp_header[i += 4], &data->win.w, 4);
	ft_memcpy(&bmp_header[i += 4], &data->win.h, 4);
	ft_memcpy(&bmp_header[i += 4], &h.planes, 2);
	ft_memcpy(&bmp_header[i += 2], &h.bpp, 2);
	ft_memset(&bmp_header[i += 2], 0, 24);
}

static void		build_pixel_data(t_data *info, int *pixel_data)
{
	int			i;
	int			j;
	int			k;

	i = info->win.h - 1;
	k = 0;
	while (i >= 0)
	{
		j = 0;
		while (j < info->win.w)
		{
			pixel_data[i * info->win.w + j] = info->img.data[k++];
			j++;
		}
		i--;
	}
}

void			create_bmp(t_data *info, char **argv)
{
	char		bmp_header[54];
	int			*pixel_data;
	uint32_t	n_pixel;
	int			fd;

	if (ft_strncmp(argv[2], "--save", 7))
		error("Missing arguments");
	draw_flor(info);
	wall_casting(info);
	sprite_casting(info);
	draw(info);
	fd = open("save.bmp", O_CREAT | O_WRONLY, 0644);
	n_pixel = info->win.h * info->win.w * 4;
	if (!(pixel_data = (int *)malloc(sizeof(int) * n_pixel)))
		exit(1);
	build_header(info, bmp_header, n_pixel);
	build_pixel_data(info, pixel_data);
	write(fd, bmp_header, 54);
	write(fd, pixel_data, n_pixel);
	close(fd);
	free(pixel_data);
	exit(0);
}
