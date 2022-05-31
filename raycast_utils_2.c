#include "cub3d.h"

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
