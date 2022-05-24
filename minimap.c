#include "cub3d.h"

static int render_rect(t_image *img, t_rect rect)
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

int	render_minimap(t_data *data)
{
	int			**map;
	t_rect		temp;
	int	width, height;

	int sqw;
	int	sqh;

	map = data->map.data;
	width = SCREEN_WIDTH / 4;
	height = SCREEN_HEIGHT / 4;

	sqw = width / data->map.x;
	sqh = height / data->map.y;
	data->minimap.width = sqw * data->map.x;
	data->minimap.height = sqh * data->map.y;

	int xp, yp = 0;
	int x,y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		xp = 0;
		while (map[y][x] != MAP_END_OF_LINE)
		{
			if (map[y][x] == MAP_TYPE_WALL)
			{
				temp.width = sqw;
				temp.height = sqh;
				temp.x0 = xp + (SCREEN_WIDTH - data->minimap.width);
				temp.y0 = yp;
				temp.color = 0xFFFFFFF;
				render_rect(&data->image, temp);
			}
			xp += sqw;
			x++;
		}
		yp += sqh;
		y++;
	}
	temp.width = sqw / 3;
	temp.height = sqh / 3;
	temp.x0 = sqw * data->pos.x + (SCREEN_WIDTH - data->minimap.width);
	temp.y0 = sqh * data->pos.y;
	temp.color = 0xFF0000;
	render_rect(&data->image, temp);

	
	return (0);
}