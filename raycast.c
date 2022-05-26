/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkane <alkane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 01:37:32 by alistair          #+#    #+#             */
/*   Updated: 2022/05/26 16:13:44 by alkane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_values(t_data *data, t_rc *rc)
{
	double	camera_x;

	camera_x = 2 * rc->px.x / (double)SCREEN_WIDTH - 1;
	rc->ray_dir.x = data->dir.x + data->camera_plane.x * camera_x;
	rc->ray_dir.y = data->dir.y + data->camera_plane.y * camera_x;
	rc->map.x = (int)data->pos.x;
	rc->map.y = (int)data->pos.y;
	if (rc->map.x != data->old_pos.x || (int)data->pos.y != data->old_pos.y)
	{
		update_map(data);
		data->old_pos.x = rc->map.x;
		data->old_pos.y = rc->map.y;
	}
	if (rc->ray_dir.x == 0)
		rc->delta_dist.x = INFINITY;
	else
		rc->delta_dist.x = fabs(1 / rc->ray_dir.x);
	if (rc->ray_dir.y == 0)
		rc->delta_dist.y = INFINITY;
	else
		rc->delta_dist.y = fabs(1 / rc->ray_dir.y);
}

static void	calc_side_dist(t_data *data, t_rc *rc)
{
	if (rc->ray_dir.x < 0)
	{
		rc->step.x = -1;
		rc->side_dist.x = (data->pos.x - rc->map.x) * rc->delta_dist.x;
	}
	else
	{
		rc->step.x = 1;
		rc->side_dist.x = (rc->map.x + 1.0 - data->pos.x) * rc->delta_dist.x;
	}
	if (rc->ray_dir.y < 0)
	{
		rc->step.y = -1;
		rc->side_dist.y = (data->pos.y - rc->map.y) * rc->delta_dist.y;
	}
	else
	{
		rc->step.y = 1;
		rc->side_dist.y = (rc->map.y + 1.0 - data->pos.y) * rc->delta_dist.y;
	}
}

static void	calc_hit(t_data *data, t_rc *rc)
{
	int	hit;
	
	hit = 0;
	while (hit == 0)
	{
		if (rc->side_dist.x < rc->side_dist.y)
		{
			rc->side_dist.x += rc->delta_dist.x;
			rc->map.x += rc->step.x;
			rc->side = 0;
		}
		else
		{
			rc->side_dist.y += rc->delta_dist.y;
			rc->map.y += rc->step.y;
			rc->side = 1;
		}
		if (data->map.data[rc->map.y][rc->map.x] > 0)
		{
			if (data->map.data[rc->map.y][rc->map.x] == MAP_TYPE_DOOR)
			{
				if (data->map.info[rc->map.y][rc->map.x].open_door == 0)
					hit = 1;
			}
			else
				hit = 1;
		}
	}
}

static void	calc_tex_x(t_data *data, t_rc *rc)
{
	double	perp_wall_distance;
	double	wall_x;

	if (rc->side == 0)
		perp_wall_distance = rc->side_dist.x - rc->delta_dist.x;
	else
		perp_wall_distance = rc->side_dist.y - rc->delta_dist.y;
	rc->line_height = (int)(SCREEN_HEIGHT / perp_wall_distance);
	rc->draw_start = -rc->line_height / 2 + SCREEN_HEIGHT / 2;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	rc->draw_end = rc->line_height / 2 + SCREEN_HEIGHT / 2;
	if (rc->draw_end >= SCREEN_HEIGHT)
		rc->draw_end = SCREEN_HEIGHT - 1;
	if (rc->side == 0)
		wall_x = data->pos.y + perp_wall_distance * rc->ray_dir.y;
	else
		wall_x = data->pos.x + perp_wall_distance * rc->ray_dir.x;
	wall_x -= floor(wall_x);
	rc->tex.x = (int)(wall_x * (double)TEX_WIDTH);
	if (rc->side == 0 && rc->ray_dir.x > 0)
		rc->tex.x = TEX_WIDTH - rc->tex.x - 1;
	if (rc->side == 1 && rc->ray_dir.y < 0)
		rc->tex.x = TEX_WIDTH - rc->tex.x - 1;
}

int	raycast(t_data *data)
{
	t_rc	rc;

	rc.px.x = -1;
	while (++rc.px.x < SCREEN_WIDTH)
	{
		init_values(data, &rc);
		calc_side_dist(data, &rc);
		calc_hit(data, &rc);
		calc_tex_x(data, &rc);
		rc.tex_step = 1.0 * TEX_HEIGHT / rc.line_height;
		rc.tex_pos = (rc.draw_start - SCREEN_HEIGHT / 2 + rc.line_height / 2) \
			* rc.tex_step;
		rc.px.y = -1;
		loop_vert_axis(data, &rc);
	}
	render_minimap(data);
	calc_move_speeds(data);
	return (0);
}
