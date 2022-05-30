// !!!!!

#include "cub3d.h"

static void	check_special_tiles(t_data *data, int x, int y);

void	key_w(t_data *data)
{
	int	y;
	int	x;

	y = (int)data->pos.y;
	x = (int)(data->pos.x + data->dir.x * data->move_speed);
	if (data->map.data[y][x] == MAP_TYPE_EMPTY_SPACE
		|| (data->map.data[y][x] == MAP_TYPE_DOOR
		&& data->map.info[y][x].open_door == 1))
	{
		data->pos.x += data->dir.x * data->move_speed;
	}
	else
		check_special_tiles(data, x, y);
	y = (int)(data->pos.y + data->dir.y * data->move_speed);
	x = (int)data->pos.x;
	if (data->map.data[y][x] == MAP_TYPE_EMPTY_SPACE
		|| (data->map.data[y][x] == MAP_TYPE_DOOR
		&& data->map.info[y][x].open_door == 1))
	{
		data->pos.y += data->dir.y * data->move_speed;
	}
	else
		check_special_tiles(data, x, y);
}

void	key_a(t_data *data)
{
	int	y;
	int	x;

	y = (int)data->pos.y;
	x = (int)(data->pos.x - data->camera_plane.x * data->move_speed);
	if (data->map.data[y][x] == MAP_TYPE_EMPTY_SPACE
		|| (data->map.data[y][x] == MAP_TYPE_DOOR
		&& data->map.info[y][x].open_door == 1))
	{
		data->pos.x -= data->camera_plane.x * data->move_speed;
	}
	else
		check_special_tiles(data, x, y);
	y = (int)(data->pos.y - data->camera_plane.y * data->move_speed);
	x = (int)data->pos.x;
	if (data->map.data[y][x] == MAP_TYPE_EMPTY_SPACE
		|| (data->map.data[y][x] == MAP_TYPE_DOOR
		&& data->map.info[y][x].open_door == 1))
	{
		data->pos.y -= data->camera_plane.y * data->move_speed;
	}
	else
		check_special_tiles(data, x, y);
}

void	key_d(t_data *data)
{
	int	y;
	int	x;

	y = (int)data->pos.y;
	x = (int)(data->pos.x + data->camera_plane.x * data->move_speed);
	if (data->map.data[y][x] == MAP_TYPE_EMPTY_SPACE
		|| (data->map.data[y][x] == MAP_TYPE_DOOR
		&& data->map.info[y][x].open_door == 1))
	{
		data->pos.x += data->camera_plane.x * data->move_speed;
	}
	else
		check_special_tiles(data, x, y);
	y = (int)(data->pos.y + data->camera_plane.y * data->move_speed);
	x = (int)data->pos.x;
	if (data->map.data[y][x] == MAP_TYPE_EMPTY_SPACE
		|| (data->map.data[y][x] == MAP_TYPE_DOOR
		&& data->map.info[y][x].open_door == 1))
	{
		data->pos.y += data->camera_plane.y * data->move_speed;
	}
	else
		check_special_tiles(data, x, y);
}

void	key_s(t_data *data)
{
	int	y;
	int	x;

	y = (int)data->pos.y;
	x = (int)(data->pos.x - data->dir.x * data->move_speed);
	if (data->map.data[y][x] == MAP_TYPE_EMPTY_SPACE
		|| (data->map.data[y][x] == MAP_TYPE_DOOR
		&& data->map.info[y][x].open_door == 1))
	{
		data->pos.x -= data->dir.x * data->move_speed;
	}
	else
		check_special_tiles(data, x, y);
	y = (int)(data->pos.y - data->dir.y * data->move_speed);
	x = (int)data->pos.x;
	if (data->map.data[y][x] == MAP_TYPE_EMPTY_SPACE
		|| (data->map.data[y][x] == MAP_TYPE_DOOR
		&& data->map.info[y][x].open_door == 1))
	{
		data->pos.y -= data->dir.y * data->move_speed;
	}
	else
		check_special_tiles(data, x, y);
}

static void	check_special_tiles(t_data *data, int x, int y)
{
	if (data->map.data[y][x] == MAP_TYPE_PORTAL)
		data->new_level = 1;
	else if (data->map.data[y][x] == MAP_TYPE_EXIT)
		data->exit++;
}
