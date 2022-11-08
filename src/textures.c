/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:49:28 by dbrandtn          #+#    #+#             */
/*   Updated: 2022/11/08 16:04:41 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	load_wall_textures(t_data *data, int width, int height);
static int	load_torch_sprites(t_data *data, int width, int height);
static int	load_portal_sprites(t_data *data, int width, int height);
static int	load_extra_textures(t_data *data, int width, int height);

int	parse_textures(t_data *data)
{
	int	tx_height;
	int	tx_width;

	tx_height = TEX_HEIGHT;
	tx_width = TEX_WIDTH;
	if (load_wall_textures(data, tx_width, tx_height) != 0)
		return (-1);
	if (load_extra_textures(data, tx_width, tx_height) != 0)
		return (-1);
	if (load_torch_sprites(data, tx_width, tx_height) != 0)
		return (-1);
	if (load_portal_sprites(data, tx_width, tx_height) != 0)
		return (-1);
	return (0);
}

static int	load_wall_textures(t_data *data, int width, int height)
{
	data->tx_no.img = mlx_xpm_file_to_image(data->mlx, data->map.tx_no,
			&width, &height);
	data->tx_so.img = mlx_xpm_file_to_image(data->mlx, data->map.tx_so,
			&width, &height);
	data->tx_ea.img = mlx_xpm_file_to_image(data->mlx, data->map.tx_ea,
			&width, &height);
	data->tx_we.img = mlx_xpm_file_to_image(data->mlx, data->map.tx_we,
			&width, &height);
	if (data->tx_no.img == NULL || data->tx_so.img == NULL
		|| data->tx_ea.img == NULL || data->tx_we.img == NULL)
		return (-1);
	data->tx_no.data = (int *)mlx_get_data_addr(data->tx_no.img,
			&data->tx_no.bpp, &data->tx_no.size_line, &data->tx_no.endian);
	data->tx_so.data = (int *)mlx_get_data_addr(data->tx_so.img,
			&data->tx_so.bpp, &data->tx_so.size_line, &data->tx_so.endian);
	data->tx_ea.data = (int *)mlx_get_data_addr(data->tx_ea.img,
			&data->tx_ea.bpp, &data->tx_ea.size_line, &data->tx_ea.endian);
	data->tx_we.data = (int *)mlx_get_data_addr(data->tx_we.img,
			&data->tx_we.bpp, &data->tx_we.size_line, &data->tx_we.endian);
	return (0);
}

static int	load_torch_sprites(t_data *data, int width, int height)
{
	int	i;

	data->tx_torch[0].img = mlx_xpm_file_to_image(data->mlx,
			"./textures/torch_frame1.xpm", &width, &height);
	data->tx_torch[1].img = mlx_xpm_file_to_image(data->mlx,
			"./textures/torch_frame2.xpm", &width, &height);
	data->tx_torch[2].img = mlx_xpm_file_to_image(data->mlx,
			"./textures/torch_frame3.xpm", &width, &height);
	data->tx_torch[3].img = mlx_xpm_file_to_image(data->mlx,
			"./textures/torch_frame4.xpm", &width, &height);
	data->tx_torch[4].img = mlx_xpm_file_to_image(data->mlx,
			"./textures/torch_frame5.xpm", &width, &height);
	if (data->tx_torch[0].img == NULL || data->tx_torch[1].img == NULL
		|| data->tx_torch[2].img == NULL || data->tx_torch[3].img == NULL
		|| data->tx_torch[4].img == NULL)
		return (-1);
	i = 0;
	while (i < SPRITE_COUNT)
	{
		data->tx_torch[i].data = (int *)mlx_get_data_addr(
				data->tx_torch[i].img, &data->tx_torch[i].bpp,
				&data->tx_torch[i].size_line, &data->tx_torch[i].endian);
		i++;
	}
	return (0);
}

static int	load_portal_sprites(t_data *data, int width, int height)
{
	int	i;

	data->tx_portal[0].img = mlx_xpm_file_to_image(data->mlx,
			"./textures/portal_frame1.xpm", &width, &height);
	data->tx_portal[1].img = mlx_xpm_file_to_image(data->mlx,
			"./textures/portal_frame2.xpm", &width, &height);
	data->tx_portal[2].img = mlx_xpm_file_to_image(data->mlx,
			"./textures/portal_frame3.xpm", &width, &height);
	data->tx_portal[3].img = mlx_xpm_file_to_image(data->mlx,
			"./textures/portal_frame4.xpm", &width, &height);
	data->tx_portal[4].img = mlx_xpm_file_to_image(data->mlx,
			"./textures/portal_frame5.xpm", &width, &height);
	if (data->tx_portal[0].img == NULL || data->tx_portal[1].img == NULL
		|| data->tx_portal[2].img == NULL || data->tx_portal[3].img == NULL
		|| data->tx_portal[4].img == NULL)
		return (-1);
	i = 0;
	while (i < SPRITE_COUNT)
	{
		data->tx_portal[i].data = (int *)mlx_get_data_addr(
				data->tx_portal[i].img, &data->tx_portal[i].bpp,
				&data->tx_portal[i].size_line, &data->tx_portal[i].endian);
		i++;
	}
	return (0);
}

static int	load_extra_textures(t_data *data, int width, int height)
{
	data->tx_door.img = mlx_xpm_file_to_image(data->mlx,
			"./textures/door_blue.xpm", &width, &height);
	data->tx_exit.img = mlx_xpm_file_to_image(data->mlx,
			"./textures/exit.xpm", &width, &height);
	if (data->tx_door.img == NULL || data->tx_exit.img == NULL)
		return (-1);
	data->tx_door.data = (int *)mlx_get_data_addr(data->tx_door.img,
			&data->tx_door.bpp, &data->tx_door.size_line,
			&data->tx_door.endian);
	data->tx_exit.data = (int *)mlx_get_data_addr(data->tx_exit.img,
			&data->tx_exit.bpp, &data->tx_exit.size_line,
			&data->tx_exit.endian);
	return (0);
}
