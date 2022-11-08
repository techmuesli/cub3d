/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:48:23 by dbrandtn          #+#    #+#             */
/*   Updated: 2022/11/08 16:04:15 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	color_rect(t_data *data, t_vec_i pix_pos, int color)
{
	t_vec_i	square;
	t_rect	temp;

	square = calc_square(data);
	temp.width = square.x;
	temp.height = square.y;
	temp.x0 = pix_pos.x + (SCREEN_WIDTH - data->minimap.width) - 20;
	temp.y0 = pix_pos.y;
	temp.color = color;
	render_rect(&data->image, temp);
}

int	render_rect(t_image *img, t_rect rect)
{
	int	i;
	int	j;

	i = rect.y0;
	while (i < rect.y0 + rect.height)
	{
		j = rect.x0;
		while (j < rect.x0 + rect.width)
			cub3d_mlx_pixel_put(img, j++, i, rect.color);
		++i;
	}
	return (0);
}

t_vec_i	calc_square(t_data *data)
{
	t_vec_i	square;

	square.x = (SCREEN_WIDTH / 3) / data->map.x;
	square.y = (SCREEN_HEIGHT / 3) / data->map.y;
	if (data->map.x < data->map.y)
		square.y = square.x;
	else
		square.x = square.y;
	return (square);
}

void	select_square_color(t_data *data, t_vec_i map, t_vec_i pix_pos)
{
	if (data->map.info[map.y][map.x].visible >= 1)
	{
		if (data->map.data[map.y][map.x] == MAP_TYPE_EMPTY_SPACE \
			&& data->map.info[map.y][map.x].visible == 1)
			color_rect(data, pix_pos, create_trgb(0, data->map.flr.r, \
				data->map.flr.g, data->map.flr.b));
		if (data->map.info[map.y][map.x].visible == 2)
		{
			color_rect(data, pix_pos, create_trgb(0, data->map.flr.r / 2, \
				data->map.flr.g / 2, data->map.flr.b / 2));
			data->map.info[map.y][map.x].visible--;
		}
		if (data->map.data[map.y][map.x] == MAP_TYPE_WALL || \
			data->map.data[map.y][map.x] == MAP_TYPE_WALL_SPRITE)
			color_rect(data, pix_pos, return_color(data, 0));
		if (data->map.data[map.y][map.x] == MAP_TYPE_DOOR)
			color_rect(data, pix_pos, return_color(data, 1));
		if (data->map.data[map.y][map.x] == MAP_TYPE_PORTAL)
			color_rect(data, pix_pos, 0x00FF00);
		if (data->map.data[map.y][map.x] == MAP_TYPE_EXIT)
			color_rect(data, pix_pos, 0x800000);
	}
}

void	render_time(t_data *data)
{
	char		temp[MAX_LEN];
	u_int64_t	time;

	time = get_time() - data->start.start_time;
#ifdef __linux__
	sprintf(temp, "%lu.%lus", time / 1000, time % 1000);
#elif __APPLE__
	sprintf(temp, "%llu.%llus", time / 1000, time % 1000);
	mlx_set_font(data->mlx, data->window, "lucidasanstypewriter-bold-24");
#endif
	mlx_string_put(data->mlx, data->window, 50, 50, 0xFFFFFF, temp);
}
