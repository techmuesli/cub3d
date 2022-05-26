// !!!!!

#include "cub3d.h"

static void	free_textures(t_data *data);

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
	t_map *map;
	int	i;

	map = &data->map;
	free_textures(data);
	if (map->data == NULL)
		return ;
	if (map->tx_no != NULL)
		free(map->tx_no);
	if (map->tx_ea != NULL)
		free(map->tx_ea);
	if (map->tx_so != NULL)
		free(map->tx_so);
	if (map->tx_we != NULL)
		free(map->tx_we);
	i = 0;
	while (map->data[i] != NULL) // !!!!!? && map->flags[i] != NULL
	{
		free(map->data[i]);
		free(map->info[i]);
		i++;
	}
	free(map->data);
	free(map->info);
	ft_bzero(map, sizeof(t_map));
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
	i = 0;
	while (i < SPRITE_COUNT)
	{
		if (data->tx_torch[i].img != NULL)
			mlx_destroy_image(data->mlx, data->tx_torch[i].img);
		i++;
	}
	i = 0;
	while (i < SPRITE_COUNT)
	{
		if (data->tx_portal[i].img != NULL)
			mlx_destroy_image(data->mlx, data->tx_portal[i].img);
		i++;
	}
}
