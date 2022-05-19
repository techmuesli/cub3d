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
	printf("Keycode %d\n", keycode);
	if (keycode == 65307)
		end_loop(param);
	if (keycode == 119)
		key_w(data);
	if (keycode == 97)
		key_a(data);
	if (keycode == 115)
		key_s(data);
	if (keycode == 100)
		key_d(data);
	
	if (keycode == 65361)
		key_left(data);
	if (keycode == 65363)
		key_right(data);
	return (0);
}

static int	end_loop(void *param)
{
	t_data	*data;

	data = param;
	mlx_loop_end(data->mlx);
	return (0);
}
