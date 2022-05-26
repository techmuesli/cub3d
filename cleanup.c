// !!!!!

#include "cub3d.h"

static void	free_textures(t_data *data);
static void	bzero_textures(t_data *data);

void	cub3d_cleanup(t_data **data)
{
	if (*data == NULL)
		return ;
	if ((*data)->mlx != NULL)
	{
		if ((*data)->image.img != NULL)
			mlx_destroy_image((*data)->mlx, (*data)->image.img);
		if ((*data)->window != NULL)
			mlx_destroy_window((*data)->mlx, (*data)->window);
		mlx_destroy_display((*data)->mlx);
		free((*data)->mlx);
	}
	free_map(*data);
	free(*data);
	*data = NULL;
}

void	free_map(t_data *data)
{
	int	i;

	free_textures(data);
	if (data->map.data == NULL)
		return ;
	if (data->map.tx_no != NULL)
		free(data->map.tx_no);
	if (data->map.tx_ea != NULL)
		free(data->map.tx_ea);
	if (data->map.tx_so != NULL)
		free(data->map.tx_so);
	if (data->map.tx_we != NULL)
		free(data->map.tx_we);
	i = 0;
	while (data->map.data[i] != NULL)
	{
		free(data->map.data[i]);
		free(data->map.info[i]);
		i++;
	}
	free(data->map.data);
	free(data->map.info);
	ft_bzero(&data->map, sizeof(t_map));
}

static void	free_textures(t_data *data)
{
	int	i;

	if (data->tx_no.img != NULL)
		mlx_destroy_image(data->mlx, data->tx_no.img);
	if (data->tx_ea.img != NULL)
		mlx_destroy_image(data->mlx, data->tx_ea.img);
	if (data->tx_so.img != NULL)
		mlx_destroy_image(data->mlx, data->tx_so.img);
	if (data->tx_we.img != NULL)
		mlx_destroy_image(data->mlx, data->tx_we.img);
	if (data->tx_door.img != NULL)
		mlx_destroy_image(data->mlx, data->tx_door.img);
	if (data->tx_exit.img != NULL)
		mlx_destroy_image(data->mlx, data->tx_exit.img);
	i = -1;
	while (++i < SPRITE_COUNT)
	{
		if (data->tx_torch[i].img != NULL)
			mlx_destroy_image(data->mlx, data->tx_torch[i].img);
	}
	i = -1;
	while (++i < SPRITE_COUNT)
	{
		if (data->tx_portal[i].img != NULL)
			mlx_destroy_image(data->mlx, data->tx_portal[i].img);
	}
	bzero_textures(data);
}

static void	bzero_textures(t_data *data)
{
	int	i;

	ft_bzero(&data->tx_no, sizeof(t_texture));
	ft_bzero(&data->tx_so, sizeof(t_texture));
	ft_bzero(&data->tx_we, sizeof(t_texture));
	ft_bzero(&data->tx_ea, sizeof(t_texture));
	ft_bzero(&data->tx_door, sizeof(t_texture));
	i = -1;
	while (++i < SPRITE_COUNT)
	{
		ft_bzero(&data->tx_torch[i], sizeof(t_texture));
		ft_bzero(&data->tx_portal[i], sizeof(t_texture));
	}
}
