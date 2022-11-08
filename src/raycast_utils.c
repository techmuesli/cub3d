/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:48:54 by dbrandtn          #+#    #+#             */
/*   Updated: 2022/11/08 16:04:23 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	select_tx_color(t_data *data, t_rc *rc);
static void	calc_sprite_frame(t_data *data, t_rc *rc);

void	calc_wall_color(t_data *data, t_rc *rc)
{
	rc->tex.y = (int)rc->tex_pos & (TEX_HEIGHT - 1);
	rc->tex_pos += rc->tex_step;
	if (data->map.data[rc->map.y][rc->map.x] == MAP_TYPE_DOOR
		&& data->map.info[rc->map.y][rc->map.x].open_door == 0)
	{
		rc->color = data->tx_door.data[TEX_HEIGHT * rc->tex.y + rc->tex.x];
		if (rc->side == 1)
			rc->color = (rc->color >> 1) & 8355711;
	}
	else if (data->map.data[rc->map.y][rc->map.x] == MAP_TYPE_EXIT)
	{
		rc->color = data->tx_exit.data[TEX_HEIGHT * rc->tex.y + rc->tex.x];
	}
	else
	{
		select_tx_color(data, rc);
	}
	calc_sprite_frame(data, rc);
}

static void	select_tx_color(t_data *data, t_rc *rc)
{
	if (rc->side == 1)
	{					
		if (rc->ray_dir.y > 0)
			rc->color = data->tx_so.data[TEX_HEIGHT * rc->tex.y + rc->tex.x];
		else
			rc->color = data->tx_no.data[TEX_HEIGHT * rc->tex.y + rc->tex.x];
		rc->color = (rc->color >> 1) & 8355711;
	}
	else
	{
		if (rc->ray_dir.x < 0)
			rc->color = data->tx_we.data[TEX_HEIGHT * rc->tex.y + rc->tex.x];
		else
			rc->color = data->tx_ea.data[TEX_HEIGHT * rc->tex.y + rc->tex.x];
	}
}

static void	calc_sprite_frame(t_data *data, t_rc *rc)
{
	int	fr;

	if (data->map.data[rc->map.y][rc->map.x] == MAP_TYPE_WALL_SPRITE)
	{
		fr = data->map.info[rc->map.y][rc->map.x].frame_num;
		if (data->tx_torch[fr].data[TEX_HEIGHT * rc->tex.y + rc->tex.x] != 0)
			rc->color = data->tx_torch[fr].data[TEX_HEIGHT \
				* rc->tex.y + rc->tex.x];
	}
	else if (data->map.data[rc->map.y][rc->map.x] == MAP_TYPE_PORTAL)
	{
		fr = data->map.info[rc->map.y][rc->map.x].frame_num;
		if (data->tx_portal[fr].data[TEX_HEIGHT * rc->tex.y + rc->tex.x] != 0)
			rc->color = data->tx_portal[fr].data[TEX_HEIGHT \
				* rc->tex.y + rc->tex.x];
	}
}

void	calc_move_speeds(t_data *data)
{
	double	frame_time;

	data->last_time = data->current_time;
	data->current_time = get_time();
	frame_time = 1000 / (data->current_time - data->last_time);
	data->move_speed = (frame_time / 1000) * 6.0;
	data->rot_speed = (frame_time / 1000) * 3.0;
}

void	check_open_door(t_data *data, t_rc *rc)
{
	if (data->map.info[rc->map.y][rc->map.x].open_door == 0)
		rc->hit = 1;
}

void	finish_game(t_data *data)
{
	ft_bzero64(data->image.addr, SCREEN_WIDTH * SCREEN_HEIGHT
		* (data->image.bpp / 8));
	mlx_put_image_to_window(data->mlx, data->window, data->image.img, 0, 0);
	server_fetch(data);
	data->exit++;
}
