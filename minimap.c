#include "cub3d.h"

static int	render_rect(t_image *img, t_rect rect)
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

static void	color_rect(t_data *data, t_vec_i pix_pos, int color)
{
	t_vec_i	square;
	t_rect	temp;

	square.x = (SCREEN_WIDTH / 4) / data->map.x;
	square.y = (SCREEN_HEIGHT / 4) / data->map.y;

	temp.width = square.x;
	temp.height = square.y;
	temp.x0 = pix_pos.x + (SCREEN_WIDTH - data->minimap.width);
	temp.y0 = pix_pos.y;
	temp.color = color;
	render_rect(&data->image, temp);
}

static void	update_player_pos(t_data *data, t_vec_i square)
{
	t_rect	temp;

	temp.width = square.x / 3;
	temp.height = square.y / 3;

	// actual player pos
	temp.x0 = square.x * data->pos.x + (SCREEN_WIDTH - data->minimap.width);
	temp.y0 = square.y * data->pos.y;
	temp.color = 0xFF0000;
	render_rect(&data->image, temp);

	// intermittent point to dir
	temp.x0 = square.x * (data->pos.x + (data->dir.x / 4)) + (SCREEN_WIDTH - data->minimap.width);
	temp.y0 = square.y * (data->pos.y + (data->dir.y / 4));
	render_rect(&data->image, temp);

	// dir point
	temp.x0 = square.x * (data->pos.x + (data->dir.x / 2)) + (SCREEN_WIDTH - data->minimap.width);
	temp.y0 = square.y * (data->pos.y + (data->dir.y / 2));
	render_rect(&data->image, temp);


}

int	render_minimap(t_data *data)
{
	t_vec_i	square;
	t_vec_i	pix_pos;
	t_vec_i	map_pos;

	square.x = (SCREEN_WIDTH / 4) / data->map.x;
	square.y = (SCREEN_HEIGHT / 4) / data->map.y;
	data->minimap.width = square.x * data->map.x;
	data->minimap.height = square.y * data->map.y;
	pix_pos.y = 0;
	map_pos.y = 0;
	while (data->map.data[map_pos.y] != NULL)
	{
		map_pos.x = 0;
		pix_pos.x = 0;
		while (data->map.data[map_pos.y][map_pos.x] != MAP_END_OF_LINE)
		{
			if (data->map.info[map_pos.y][map_pos.x].visible == 1)
			{
				if (data->map.data[map_pos.y][map_pos.x] == MAP_TYPE_EMPTY_SPACE)
					color_rect(data, pix_pos, create_trgb(0, data->map.flr.r, \
						data->map.flr.g, data->map.flr.b));
				if (data->map.data[map_pos.y][map_pos.x] == MAP_TYPE_WALL)
					color_rect(data, pix_pos, 0xFFFFFFF);
				if (data->map.data[map_pos.y][map_pos.x] == MAP_TYPE_DOOR)
					color_rect(data, pix_pos, 0xCC6600);
			}
			pix_pos.x += square.x;
			map_pos.x++;
		}
		pix_pos.y += square.y;
		map_pos.y++;
	}
	update_player_pos(data, square);
	return (0);
}

void	update_map(t_data *data)
{
	t_vec_i	pos;
	t_vec_i	i;
	t_vec_i	end;
	t_vec_i	limit;

	pos.x = (int)data->pos.x;
	pos.y = (int)data->pos.y;
	end.x = pos.x + 2;
	end.y = pos.y + 2;
	limit.x = data->map.x;
	limit.y = data->map.y;
	i.y = pos.y - 2;
	// printf("Pos x:%d\tPos y:%d\n", (int)data->pos.x, (int)data->pos.y);
	while (i.y <= end.y)
	{
		i.x = pos.x - 2;
		while (i.x <= end.x)
		{
			if (i.x >= 0 && i.y >= 0 && i.x <= limit.x && i.y <= limit.y)
				data->map.info[i.y][i.x].visible = 1;
			i.x++;
		}
		i.y++;
	}
}
