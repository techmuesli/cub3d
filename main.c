// !!!!!

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_data	*data;

	if (argc != 2)
	{
		ft_putstr_fd("Error! - wrong amount of arguments!\n", FD_STDERR);
		return (1);
	}
	data = fdf_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	if (data == NULL)
	{
		ft_putstr_fd("Error! - init() failed!\n", FD_STDERR);
		return (1);
	}
	if (read_input_file(data, argv[1]) != 0 || parse_textures(data) != 0)
	{
		ft_putstr_fd("Error! - reading the input files failed!\n", FD_STDERR);
		fdf_cleanup(&data);
		return (1);
	}
	mlx_loop(data->mlx);
	fdf_cleanup(&data);
	return (0);
}
