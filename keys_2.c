/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:48:02 by dbrandtn          #+#    #+#             */
/*   Updated: 2022/06/10 12:59:42 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	key_f(t_data *data)
{
	int	x;
	int	y;

	x = (int)data->pos.x;
	y = (int)data->pos.y;
	if (data->map.data[y][x + 1] == MAP_TYPE_DOOR)
		check_door(data, y, x + 1);
	if (data->map.data[y][x - 1] == MAP_TYPE_DOOR)
		check_door(data, y, x - 1);
	if (data->map.data[y + 1][x] == MAP_TYPE_DOOR)
		check_door(data, y + 1, x);
	if (data->map.data[y - 1][x] == MAP_TYPE_DOOR)
		check_door(data, y - 1, x);
}
