// !!!!!

#include "cub3d.h"

// !!!!! set data->pos.x & .y

static int	check_map(int **map, t_vec *pos);

int	check_input(t_data *data)
{
	if (data->map.tx_no == NULL || data->map.tx_ea == NULL 
		|| data->map.tx_so == NULL || data->map.tx_we == NULL)
		return (-1);
	if (data->map.floor.r == -1 || data->map.floor.g == -1 
		| data->map.floor.b == -1)
		return (-1);
	if (data->map.ceiling.r == -1 || data->map.ceiling.g == -1 
		| data->map.ceiling.b == -1)
		return (-1);
	if (check_map(data->map.data, &data->pos) != 0)
		return (-1);
	return (0);
}

static int	check_map(int **map, t_vec *pos)
{
	int	x;
	int	y;

	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != MAP_END_OF_LINE)
		{
			if (map[y][x] == MAP_TYPE_N || map[y][x] == MAP_TYPE_E
				|| map[y][x] == MAP_TYPE_S || map[y][x] == MAP_TYPE_W)
			{
				if (pos->x != 0 || pos->y != 0)
					return (-1);
				pos->x = x;
				pos->y = y;
			}
			if (map[y][x] == MAP_TYPE_UNKNOWN)
				return (-1);
			x++;
		}
		y++;
	}
	return (0);
}
