/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:49:12 by dbrandtn          #+#    #+#             */
/*   Updated: 2022/11/08 16:04:34 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	load_new_map(t_data *data);
static void	change_sprite_frames(t_data *data, int x, int y);
static void	update_sprites(t_data *data);
static void	update_fps(t_data *data);

int	run_loop(void *param)
{
	t_data			*data;

	data = param;
	if (data->new_level == 1)
	{
		if (load_new_map(data) == 1)
		{
			end_loop(data);
			return (0);
		}
	}
	if (data->exit == 1)
		finish_game(data);
	else if (data->exit == 0)
	{
		if (data->start_timer == 0)
		{
			data->current_time = 0;
			data->start.start_time = get_time();
			data->initial_time = get_time();
		}
		ft_bzero64(data->image.addr, SCREEN_WIDTH * SCREEN_HEIGHT * (data->image.bpp / 8));
		raycast(data);
		update_fps(data);
		update_sprites(data);
		mlx_put_image_to_window(data->mlx, data->window, data->image.img, 0, 0);
		if (data->start_timer == 1)
			render_time(data);
	}
	return (0);
}

static int	load_new_map(t_data *data)
{
	int	level;

	free_map(data);
	data->pos.x = 0;
	data->pos.y = 0;
	data->current_time = 0;
	data->initial_time = get_time();
	data->map.flr.r = -1;
	data->map.flr.g = -1;
	data->map.flr.b = -1;
	data->map.ceiling.r = -1;
	data->map.ceiling.g = -1;
	data->map.ceiling.b = -1;
	if (ft_strcmp(data->level, LEVEL_1) == 0)
	{
		data->level = LEVEL_2;
		level = 2;
	}
	else
	{
		data->level = LEVEL_3;
		level = 3;
	}
	if (read_input_file(data, level) != 0 || parse_textures(data) != 0)
	{
		ft_putstr_fd("Error! - loading new map!\n", FD_STDERR);
		return (1);
	}
	data->new_level = 0;
	return (0);
}

static void	change_sprite_frames(t_data *data, int x, int y)
{
	if (data->current_time - data->map.info[y][x].sprite_time > 100)
	{
		if (data->map.info[y][x].frame_num == 4)
			data->map.info[y][x].frame_num = 0;
		else
			data->map.info[y][x].frame_num++;
		data->map.info[y][x].sprite_time = get_time();
	}
}

static void	update_sprites(t_data *data)
{
	int				x;
	int				y;

	y = 0;
	if (get_time() - data->start.start_time > 5000)
		data->start.start_flag = 0;
	while (data->map.data[y] != NULL)
	{
		x = 0;
		while (data->map.data[y][x] != MAP_END_OF_LINE)
		{
			if (data->map.data[y][x] == MAP_TYPE_WALL_SPRITE
				|| data->map.data[y][x] == MAP_TYPE_PORTAL)
				change_sprite_frames(data, x, y);
			x++;
		}
		y++;
	}
}

static void	update_fps(t_data *data)
{
	data->frames++;
	if (data->current_time - data->initial_time >= 1000)
	{
		ft_printf("%d\n", (data->frames));
		data->frames = 0;
		data->initial_time += 1000;
	}
}
