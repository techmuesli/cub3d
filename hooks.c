// !!!!!

#include "cub3d.h"

static int	key_cb(int keycode, void *param);
static int	end_loop(void *param);

// 17 = ON_DESTROY
void	set_up_hooks(void *window, t_data *data)
{
	mlx_key_hook(window, key_cb, data);
	mlx_hook(window, 17, 0, end_loop, data);
	mlx_loop_hook(data->mlx, run_loop, data);
}

// keycode 65307 = 'esc'
static int	key_cb(int keycode, void *param)
{
	t_data	*data;

	data = param;
	if (keycode == 65307)
		end_loop(param);
	return (0);
}

static int	end_loop(void *param)
{
	t_data	*data;

	data = param;
	mlx_loop_end(data->mlx);
	return (0);
}
