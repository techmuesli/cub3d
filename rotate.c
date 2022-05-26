#include "cub3d.h"

void	check_door(t_data *data, int y, int x)
{
	if (data->map.info[y][x].open_door == 1)
		data->map.info[y][x].open_door = 0;
	else
		data->map.info[y][x].open_door = 1;
}

void	key_left(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->dir.x;
	data->dir.x = data->dir.x * cos(-data->rot_speed) - data->dir.y * \
		sin(-data->rot_speed);
	data->dir.y = old_dir_x * sin(-data->rot_speed) + data->dir.y * \
		cos(-data->rot_speed);
	old_plane_x = data->camera_plane.x;
	data->camera_plane.x = data->camera_plane.x * \
		cos(-data->rot_speed) - data->camera_plane.y * sin(-data->rot_speed);
	data->camera_plane.y = old_plane_x * \
		sin(-data->rot_speed) + data->camera_plane.y * cos(-data->rot_speed);
}

void	key_right(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->dir.x;
	data->dir.x = data->dir.x * cos(data->rot_speed) - data->dir.y * \
		sin(data->rot_speed);
	data->dir.y = old_dir_x * sin(data->rot_speed) + data->dir.y * \
		cos(data->rot_speed);
	old_plane_x = data->camera_plane.x;
	data->camera_plane.x = data->camera_plane.x * \
		cos(data->rot_speed) - data->camera_plane.y * sin(data->rot_speed);
	data->camera_plane.y = old_plane_x * \
		sin(data->rot_speed) + data->camera_plane.y * cos(data->rot_speed);
}
