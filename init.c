// !!!!!

#include "cub3d.h"

static int	init_image(t_data *data, int width, int height);
static void	init_general_values(t_data *data);

t_data	*fdf_init(int width, int height, char *title)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data->mlx = mlx_init();
	if (data->mlx == NULL)
	{
		free(data);
		return (NULL);
	}
	data->window = mlx_new_window(data->mlx, width, height, title);
	if (data->window == NULL)
	{
		fdf_cleanup(&data);
		return (NULL);
	}
	if (init_image(data, width, height) != 0)
	{
		fdf_cleanup(&data);
		return (NULL);
	}
	mlx_mouse_hide(data->mlx, data->window);
	set_up_hooks(data->window, data);
	init_general_values(data);
	return (data);
}

static int	init_image(t_data *data, int width, int height)
{
	data->image.img = mlx_new_image(data->mlx, width, height);
	if (data->image.img == NULL)
		return (1);
	data->image.addr = mlx_get_data_addr(data->image.img,
			&data->image.bpp, &data->image.size_line,
			&data->image.endian);
	if (data->image.addr == NULL)
		return (1);
	return (0);
}

static void	init_general_values(t_data *data)
{
	// data->dir.x = -1;
	// data->dir.y = 0;
	//data->camera_plane.x = 1;
	//data->camera_plane.y = 0; // FOV = 2 * atan(data->camera_plane.y/ 1.0)
	data->current_time = 0;
	data->last_time = get_time();

	data->map.flr.r = -1;
	data->map.flr.g = -1;
	data->map.flr.b = -1;
	data->map.ceiling.r = -1;
	data->map.ceiling.g = -1;
	data->map.ceiling.b = -1;

	data->mouse_pos.x = SCREEN_WIDTH / 2; // starts with mouse in middle of screen
	data->mouse_pos.y = SCREEN_HEIGHT / 2;
}
