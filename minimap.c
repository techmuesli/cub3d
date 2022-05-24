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

int	init_minimap(t_data *data)
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

	data->minimap.img.img = mlx_new_image(data->mlx, data->minimap.width, data->minimap.height);
	if (data->minimap.img.img == NULL)
		return (1);
	data->minimap.img.addr = mlx_get_data_addr(data->minimap.img.img, &data->minimap.img.bpp,
		&data->minimap.img.size_line, &data->minimap.img.endian);
	if (data->minimap.img.addr == NULL)
		return (1);


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
				temp.x0 = xp;
				temp.y0 = yp;
				temp.color = 0xFFFFFFF;
				render_rect(&data->minimap.img, temp);
			}
			xp += sqw;
			x++;
		}
		yp += sqh;
		y++;
	}
	return (0);
}