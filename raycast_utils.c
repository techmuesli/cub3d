// !!!!!

#include "cub3d.h"

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

void	loop_vert_axis(t_data *data, t_rc *rc)
{
	while (++rc->px.y < SCREEN_HEIGHT)
	{
		if (rc->px.y < rc->draw_start)
			rc->color = create_trgb(0, data->map.ceiling.r, data->map.ceiling.g, \
				data->map.ceiling.b);
		else if (rc->px.y >= rc->draw_start && rc->px.y <= rc->draw_end)
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
				rc->color = data->tx_exit.data[TEX_HEIGHT * rc->tex.y + rc->tex.x];
			else
				select_tx_color(data, rc);
			calc_sprite_frame(data, rc);
		}
		else
			rc->color = create_trgb(0, data->map.flr.r, data->map.flr.g, \
				data->map.flr.b);
		cub3d_mlx_pixel_put(&data->image, rc->px.x, rc->px.y, rc->color);
	}
}

void	calc_move_speeds(t_data *data)
{
	double	frame_time;

	data->last_time = data->current_time;
	data->current_time = get_time();
	frame_time = 1000 / (data->current_time - data->last_time);
	data->move_speed = (frame_time / 1000) * 5.0;
	data->rot_speed = (frame_time / 1000) * 3.0;
}
