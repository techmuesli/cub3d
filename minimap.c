// !!!!!

#include "cub3d.h"

static void	update_player_pos(t_data *data, t_vec_i square)
{
	t_rect	temp;

	temp.width = square.x / 3;
	temp.height = square.y / 3;
	temp.x0 = square.x * data->pos.x + \
		(SCREEN_WIDTH - data->minimap.width) - 20;
	temp.y0 = square.y * data->pos.y + 20;
	temp.color = 0xFF0000;
	render_rect(&data->image, temp);
	temp.x0 = square.x * (data->pos.x + (data->dir.x / 4)) + \
		(SCREEN_WIDTH - data->minimap.width) - 20;
	temp.y0 = square.y * (data->pos.y + (data->dir.y / 4)) + 20;
	render_rect(&data->image, temp);
	temp.x0 = square.x * (data->pos.x + (data->dir.x / 2)) + \
		(SCREEN_WIDTH - data->minimap.width) - 20;
	temp.y0 = square.y * (data->pos.y + (data->dir.y / 2)) + 20;
	render_rect(&data->image, temp);
}

void	render_minimap(t_data *data)
{
	t_vec_i	square;
	t_vec_i	pix_pos;
	t_vec_i	map;

	square.x = (SCREEN_WIDTH / 4) / data->map.x;
	square.y = (SCREEN_HEIGHT / 4) / data->map.y;
	data->minimap.width = square.x * data->map.x;
	data->minimap.height = square.y * data->map.y;
	pix_pos.y = 0;
	map.y = -1;
	while (data->map.data[++map.y] != NULL)
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

void	update_map(t_data *data)
{
	t_vec_i	pos;
	t_vec_i	i;
	t_vec_i	end;

	pos.x = (int)data->pos.x;
	pos.y = (int)data->pos.y;
	end.x = pos.x + 2;
	end.y = pos.y + 2;
	i.y = pos.y - 2;
	while (i.y < end.y)
	{
		i.x = pos.x - 2;
		while (i.x < end.x)
		{
			if (i.x >= 0 && i.y >= 0 && i.x <= data->map.x && \
				i.y <= data->map.y)
				data->map.info[i.y][i.x].visible = 1;
			i.x++;
		}
		i.y++;
	}
}
