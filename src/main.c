/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkikuchi <kkikuchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 12:08:52 by kkikuchi          #+#    #+#             */
/*   Updated: 2021/01/10 02:18:51 by kikuchika        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int				main_loop(t_data *info)
{
	draw_flor(info);
	wall_casting(info);
	sprite_casting(info);
	draw(info);
	mlx_put_image_to_window(info->mlx, info->win.ptr, info->img.img, 0, 0);
	key_update(info);
	return (0);
}

void			init_data(t_data *data)
{
	int			i;

	i = 0;
	data->key.key_a = 0;
	data->key.key_w = 0;
	data->key.key_s = 0;
	data->key.key_d = 0;
	data->key.key_esc = 0;
	data->key.key_right = 0;
	data->key.key_left = 0;
	data->pos_x = -42;
	while (i < MAP_HEIGHT)
		ft_memset(data->map[i++], '0', MAP_WIDTH);
	data->color[0] = UINT32_MAX;
	data->color[1] = UINT32_MAX;
	data->mlx = mlx_init();
	data->sp_n = 0;
	data->sp_max = 0;
	data->win.w = -42;
	data->move_speed = 0.05;
	data->rot_speed = 0.05;
}

int				quit(t_data *data)
{
	int i;

	i = 0;
	while (i < 5)
		free(data->tex[i++].addr);
	exit(0);
	return (0);
}

void			init_buf(t_data *data)
{
	int			y;
	int			x;

	y = 0;
	if (!(data->buf = (int **)malloc(sizeof(int *) * data->win.h)))
		error("malloc失敗");
	while (y < data->win.h)
	{
		if (!(data->buf[y] = (int *)malloc(sizeof(int) * data->win.w)))
			error("malloc失敗");
		x = 0;
		while (x < data->win.w)
		{
			data->buf[y][x] = 0;
			x++;
		}
		y++;
	}
	if (!(data->z_buffer = (double *)malloc(sizeof(double) * data->win.w)))
		error("malloc失敗");
}

int				main(int argc, char **argv)
{
	t_data		data;

	if (argc < 2 || 3 < argc)
		error("Missing arguments.");
	init_data(&data);
	read_cubfile(&data, argv[1]);
	init_buf(&data);
	check_map(&data);
	data.img.img = mlx_new_image(data.mlx, data.win.w, data.win.h);
	data.img.data = (int *)mlx_get_data_addr(data.img.img, &data.img.bpp,
					&data.img.size_l, &data.img.endian);
	if (argc == 3)
		create_bmp(&data, argv);
	mlx_loop_hook(data.mlx, &main_loop, &data);
	data.win.ptr = mlx_new_window(data.mlx, data.win.w, data.win.h, "mlx");
	mlx_hook(data.win.ptr, X_EVENT_KEY_PRESS, 1L << 0, &key_press, &data);
	mlx_hook(data.win.ptr, X_EVENT_KEY_RELEASE, 1L << 1, &key_release, &data);
	mlx_hook(data.win.ptr, 33, 1L << 17, &quit, &data);
	mlx_loop(data.mlx);
	return (0);
}
