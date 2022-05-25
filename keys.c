// !!!!!

#include "cub3d.h"

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
	y = (int)(data->pos.y + data->dir.y * data->move_speed);
	x = (int)data->pos.x;
	if (data->map.data[y][x] == MAP_TYPE_EMPTY_SPACE
		|| (data->map.data[y][x] == MAP_TYPE_DOOR
		&& data->map.info[y][x].open_door == 1))
	{
		data->pos.y += data->dir.y * data->move_speed;
	}
}

void	key_a(t_data *data)
{
	int	y;
	int	x;

	y = (int)data->pos.y;
	x = (int)(int)(data->pos.x - data->camera_plane.x * data->move_speed);
	if (data->map.data[y][x] == MAP_TYPE_EMPTY_SPACE
		|| (data->map.data[y][x] == MAP_TYPE_DOOR
		&& data->map.info[y][x].open_door == 1))
	{
		data->pos.x -= data->camera_plane.x * data->move_speed;
	}
	y = (int)(data->pos.y - data->camera_plane.y * data->move_speed);
	x = (int)data->pos.x;
	if (data->map.data[y][x] == MAP_TYPE_EMPTY_SPACE
		|| (data->map.data[y][x] == MAP_TYPE_DOOR
		&& data->map.info[y][x].open_door == 1))
	{
		data->pos.y -= data->camera_plane.y * data->move_speed;
	}
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
	y = (int)(data->pos.y + data->camera_plane.y * data->move_speed);
	x = (int)data->pos.x;
	if (data->map.data[y][x] == MAP_TYPE_EMPTY_SPACE
		|| (data->map.data[y][x] == MAP_TYPE_DOOR
		&& data->map.info[y][x].open_door == 1))
	{
		data->pos.y += data->camera_plane.y * data->move_speed;
	}
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
	y = (int)(data->pos.y - data->dir.y * data->move_speed);
	x = (int)data->pos.x;
	if (data->map.data[y][x] == MAP_TYPE_EMPTY_SPACE
		|| (data->map.data[y][x] == MAP_TYPE_DOOR
		&& data->map.info[y][x].open_door == 1))
	{
		data->pos.y -= data->dir.y * data->move_speed;
	}
}

void	key_f(t_data *data)
{
	int	x;
	int	y;

	x = (int)data->pos.x;
	y = (int)data->pos.y;
	if (data->map.data[y][x + 1] == MAP_TYPE_DOOR)
	{
		if (data->map.info[y][x + 1].open_door == 1)
			data->map.info[y][x + 1].open_door = 0;
		else
			data->map.info[y][x + 1].open_door = 1;
	}
	else if (data->map.data[y][x - 1] == MAP_TYPE_DOOR)
	{
		if (data->map.info[y][x - 1].open_door == 1)
			data->map.info[y][x - 1].open_door = 0;
		else
			data->map.info[y][x - 1].open_door = 1;
	}
	else if (data->map.data[y + 1][x] == MAP_TYPE_DOOR)
	{
		if (data->map.info[y + 1][x].open_door == 1)
			data->map.info[y + 1][x].open_door = 0;
		else
			data->map.info[y + 1][x].open_door = 1;
	}
	else if (data->map.data[y - 1][x] == MAP_TYPE_DOOR)
	{
		if (data->map.info[y - 1][x].open_door == 1)
			data->map.info[y - 1][x].open_door = 0;
		else
			data->map.info[y - 1][x].open_door = 1;
	}
}

void	key_left(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->dir.x;
	data->dir.x = data->dir.x * cos(-data->rot_speed) - data->dir.y * sin(-data->rot_speed);
	data->dir.y = old_dir_x * sin(-data->rot_speed) + data->dir.y * cos(-data->rot_speed); 
	old_plane_x = data->camera_plane.x;
	data->camera_plane.x = data->camera_plane.x * cos(-data->rot_speed) - data->camera_plane.y * sin(-data->rot_speed);
	data->camera_plane.y = old_plane_x * sin(-data->rot_speed) + data->camera_plane.y * cos(-data->rot_speed);
}

void	key_right(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->dir.x;
	data->dir.x = data->dir.x * cos(data->rot_speed) - data->dir.y * sin(data->rot_speed);
	data->dir.y = old_dir_x * sin(data->rot_speed) + data->dir.y * cos(data->rot_speed); 
	old_plane_x = data->camera_plane.x;
	data->camera_plane.x = data->camera_plane.x * cos(data->rot_speed) - data->camera_plane.y * sin(data->rot_speed);
	data->camera_plane.y = old_plane_x * sin(data->rot_speed) + data->camera_plane.y * cos(data->rot_speed);
}