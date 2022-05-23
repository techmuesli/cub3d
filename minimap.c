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
	t_minimap	mm;
	int			**map;
	t_rect		temp;

	mm = data->minimap;
	map = data->map.data;

	mm.width = SCREEN_WIDTH / 10;
	mm.height = SCREEN_HEIGHT / 10;
	mm.img.img = mlx_new_image(data->mlx, mm.width, mm.height);
	if (mm.img.img == NULL)
		return (1);
	mm.img.addr = mlx_get_data_addr(mm.img.img, &mm.img.bpp, 
		&mm.img.size_line, &mm.img.endian);
	if (mm.img.addr == NULL)
		return (1);

	int sqw;
	int	sqh;

	sqw = mm.width / data->map.x;
	sqh = mm.height / data->map.y;

	int xp = 0;
	int yp = 0;

	int x,y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != MAP_END_OF_LINE)
		{
			if (map[y][x] == MAP_TYPE_WALL)
			{
				temp.width = sqw;
				temp.height = sqh;
				temp.x0 = xp;
				temp.y0 = yp;
				temp.color = 0x0;
				render_rect(mm.img.img, temp);
			}
			xp += sqw;
			x++;
		}
		yp += sqh;
		y++;
	}
	return (0);
}