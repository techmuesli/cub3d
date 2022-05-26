// !!!!!

#include "cub3d.h"

static void	change_sprite_frames(t_data *data, int x, int y);

int	run_loop(void *param)
{
	int				x;
	int				y;
	t_data			*data;
	static int		frames; // !!!!!

	data = param;
	ft_bzero64(data->image.addr, SCREEN_WIDTH * SCREEN_HEIGHT
		* (data->image.bpp / 8));
	raycast(data);
	frames++;
	if (data->current_time - data->initial_time >= 1000)
	{
		ft_printf("%d\n", (frames));
		frames = 0;
		data->initial_time += 1000;
	}
	y = 0;
	while (data->map.data[y] != NULL)
	{
		x = 0;
		while (data->map.data[y][x] != MAP_END_OF_LINE)
		{
			if (data->map.data[y][x] == MAP_TYPE_WALL_SPRITE)
				(void)change_sprite_frames(data, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->window, data->image.img, 0, 0);
	return (0);
}

static void	change_sprite_frames(t_data *data, int x, int y)
{
	if (data->current_time - data->map.info[y][x].sprite_time > 250)
	{
		if (data->map.info[y][x].frame_num == 3)
			data->map.info[y][x].frame_num = 0;
		else
			data->map.info[y][x].frame_num++;
		data->map.info[y][x].sprite_time = get_time();
	}
}
