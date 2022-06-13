/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alistair <alistair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:48:32 by dbrandtn          #+#    #+#             */
/*   Updated: 2022/06/13 16:29:04 by alistair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	return_color(t_data *data, int flag)
{
	int	wall_color;
	int	door_color;

	wall_color = 0xFFFFFF;
	door_color = 0xCC6600;
	if (ft_strcmp(data->level, LEVEL_3) == 0)
	{
		wall_color = 0x000000;
		door_color = 0x2B1D14;
	}
	if (flag == 1)
		return (door_color);
	return (wall_color);
}

static void	update_player_pos(t_data *data, t_vec_i square)
{
	t_rect	temp;

	temp.width = square.x / 3;
	temp.height = square.y / 3;
	temp.x0 = square.x * data->pos.x + \
		(SCREEN_WIDTH - data->minimap.width) - 20;
	temp.y0 = (square.y * data->pos.y) + 20;
	temp.color = 0xFF0000;
	render_rect(&data->image, temp);
	temp.x0 = square.x * (data->pos.x + (data->dir.x / 4)) + \
		(SCREEN_WIDTH - data->minimap.width) - 20;
	temp.y0 = (square.y * (data->pos.y + (data->dir.y / 4))) + 20;
	render_rect(&data->image, temp);
	temp.x0 = square.x * (data->pos.x + (data->dir.x / 2)) + \
		(SCREEN_WIDTH - data->minimap.width) - 20;
	temp.y0 = (square.y * (data->pos.y + (data->dir.y / 2))) + 20;
	render_rect(&data->image, temp);
}

void	render_minimap(t_data *data)
{
	t_vec_i	square;
	t_vec_i	pix_pos;
	t_vec_i	map;

	square = calc_square(data);
	data->minimap.width = square.x * data->map.x;
	data->minimap.height = square.y * data->map.y;
	pix_pos.y = 20;
	map.y = -1;
	while (data->map.data[++map.y] != NULL && data->exit == 0)
	{
		map.x = -1;
		pix_pos.x = 0;
		while (data->map.data[map.y][++map.x] != MAP_END_OF_LINE)
		{
			select_square_color(data, map, pix_pos);
			pix_pos.x += square.x;
		}
		pix_pos.y += square.y;
	}
	update_player_pos(data, square);
}
