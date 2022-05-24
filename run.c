// !!!!!

#include "cub3d.h"

int	run_loop(void *param)
{
	t_data			*data;
	//static int		frames;

	data = param;
	ft_bzero64(data->image.addr, SCREEN_WIDTH * SCREEN_HEIGHT
		* (data->image.bpp / 8));

	// TODO !!!!!
	// if (raycast(data) != 0)
		// ;

	raycast(data);
	
	mlx_put_image_to_window(data->mlx, data->window, data->image.img, 0, 0);

	// data->current_time = get_time();
	//frames++;
	// if (data->current_time - data->last_time >= 1000)
	// {
	// 	ft_printf("%d\n", (frames));
	// 	frames = 0;
	// 	data->last_time += 1000;
	// }
	return (0);
}
