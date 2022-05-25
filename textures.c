// !!!!!

#include "cub3d.h"

int	parse_textures(t_data *data)
{
	int	i;
	int	tx_height;
	int	tx_width;

	tx_height = TEX_HEIGHT;
	tx_width = TEX_WIDTH;
	data->tx_no.img = mlx_xpm_file_to_image(data->mlx, \
		data->map.tx_no, &tx_height, &tx_width);
	data->tx_so.img = mlx_xpm_file_to_image(data->mlx, \
		data->map.tx_so, &tx_height, &tx_width);
	data->tx_ea.img = mlx_xpm_file_to_image(data->mlx, \
		data->map.tx_ea, &tx_height, &tx_width);
	data->tx_we.img = mlx_xpm_file_to_image(data->mlx, \
		data->map.tx_we, &tx_height, &tx_width);
	data->tx_door.img = mlx_xpm_file_to_image(data->mlx,
			data->map.tx_door, &tx_height, &tx_width);
	i = 0;
	while (i < SPRITE_COUNT)
	{
		data->tx_sprite[i].img = mlx_xpm_file_to_image(data->mlx,
				data->map.tx_sprite[i], &tx_height, &tx_width);
		if (&data->tx_sprite[i] == NULL)
			return (1);
		data->tx_sprite[i].data = (int *)mlx_get_data_addr(data->tx_sprite[i].img,
			&data->tx_sprite[i].bpp, &data->tx_sprite[i].size_line,
			&data->tx_sprite[i].endian);
		i++;
	}
	if (data->tx_no.img == NULL || data->tx_so.img == NULL
		|| data->tx_ea.img == NULL || data->tx_we.img == NULL
		|| data->tx_door.img == NULL)
		return (1);
	data->tx_no.data = (int *)mlx_get_data_addr(data->tx_no.img, \
		&data->tx_no.bpp, &data->tx_no.size_line, &data->tx_no.endian);
	data->tx_so.data = (int *)mlx_get_data_addr(data->tx_so.img, \
		&data->tx_so.bpp, &data->tx_so.size_line, &data->tx_so.endian);
	data->tx_ea.data = (int *)mlx_get_data_addr(data->tx_ea.img, \
		&data->tx_ea.bpp, &data->tx_ea.size_line, &data->tx_ea.endian);
	data->tx_we.data = (int *)mlx_get_data_addr(data->tx_we.img, \
		&data->tx_we.bpp, &data->tx_we.size_line, &data->tx_we.endian);
	data->tx_door.data = (int *)mlx_get_data_addr(data->tx_door.img,
			&data->tx_door.bpp, &data->tx_door.size_line,
			&data->tx_door.endian);
	return (0);
}