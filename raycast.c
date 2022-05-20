// !!!!!

#include <stdio.h>
#include "cub3d.h"

static void	draw_vert_line(t_data *data, int x, int start, int end, int color);

int	raycast(t_data *data)
{
	double	camera_x;
	double	perp_wall_distance; // perpendicular
	double	frame_time;
	int		x;
	int		hit;
	int		draw_start;
	int		draw_end;
	int		line_height;
	int		side;
	int		color;
	t_vec	ray_direction;
	t_vec	side_distance;
	t_vec	delta_distance;
	t_vec_i	step;
	t_vec_i	map;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		ray_direction.x = data->dir.x + data->camera_plane.x * camera_x;
		ray_direction.y = data->dir.y + data->camera_plane.y * camera_x;
		map.x = (int)data->pos.x;
		map.y = (int)data->pos.y;
		hit = 0;
		if (ray_direction.x == 0)
			delta_distance.x = INFINITY;
		else
			delta_distance.x = fabs(1/ ray_direction.x);
		if (ray_direction.y == 0)
			delta_distance.y = INFINITY;
		else
			delta_distance.y = fabs(1/ ray_direction.y);
		if (ray_direction.x < 0)
		{
			step.x = -1;
			side_distance.x = (data->pos.x - map.x) * delta_distance.x;
		}
		else
		{
			step.x = 1;
			side_distance.x = (map.x + 1.0 - data->pos.x) * delta_distance.x;
		}
		if (ray_direction.y < 0)
		{
			step.y = -1;
			side_distance.y = (data->pos.y - map.y) * delta_distance.y;
		}
		else
		{
			step.y = 1;
			side_distance.y = (map.y + 1.0 - data->pos.y) * delta_distance.y;
		}
		while (hit == 0)
		{
			if (side_distance.x < side_distance.y)
			{
				side_distance.x += delta_distance.x;
				map.x += step.x;
				side = 0;
			}
			else
			{
				side_distance.y += delta_distance.y;
				map.y += step.y;
				side = 1;
			}
			if (data->map.data[map.y][map.x] > 0)
				hit = 1;
		}
		if (side == 0)
			perp_wall_distance = side_distance.x - delta_distance.x;
		else
			perp_wall_distance = side_distance.y - delta_distance.y;
		line_height = (int)(SCREEN_HEIGHT / perp_wall_distance);
		draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_end >= SCREEN_HEIGHT)
			draw_end = SCREEN_HEIGHT - 1;
		
		int	tex_num = data->map.data[map.x][map.y] - 1;
		double	wall_x;

		if (side == 0)
			wall_x = data->pos.y + perp_wall_distance * ray_direction.y;
		else
			wall_x = data->pos.x + perp_wall_distance * ray_direction.x;
		wall_x -= floor(wall_x);

		int	tex_x;
		tex_x = (int)(wall_x * (double)TEXTURE_WIDTH);
		if (side == 0 && ray_direction.x > 0)
			tex_x = TEXTURE_WIDTH - tex_x - 1;
		if (side == 1 && ray_direction.y < 0)
			tex_x = TEXTURE_WIDTH - tex_x - 1;

	

		double step = 1.0 * TEXTURE_HEIGHT / line_height;
		double tex_pos = (draw_start - SCREEN_HEIGHT / 2 + line_height / 2) * step;
		int y = draw_start - 1;
		int tex_y;
		while (++y < draw_end)
		{
			tex_y = (int)tex_pos & (TEXTURE_HEIGHT - 1);
			tex_pos += step;
			color = data->tx_no.data[TEXTURE_HEIGHT * tex_y + tex_x]; // !!!!!
			if (side == 1)
				color = (color >> 1) & 8355711;
			cub3d_mlx_pixel_put(&data->image, x, y, color);
		}


		// color = 0xffffff; // !!!!!
		// if (side == 1)
		// 	color /= 2; // !!!!!
		// draw_vert_line(data, x, draw_start, draw_end, color);
		x++;
	}
	data->last_time = data->current_time;
	data->current_time = get_time();
	frame_time = 1000 / (data->current_time - data->last_time); // seconds
	//printf("Frame time: %f\n", frame_time);
	data->move_speed = (frame_time / 1000) * 5.0;
	data->rot_speed = (frame_time / 1000) * 3.0;
	return (0);
}

static void	draw_vert_line(t_data *data, int x, int start, int end, int color)
{
	int	y;

	y = start;
	while (y < end)
	{
		cub3d_mlx_pixel_put(&data->image, x, y, color);
		y++;
	}
}
