// !!!!!

#include "cub3d.h"

static void	free_map(t_map *map);
static void	free_textures(t_data *data);

void	cub3d_cleanup(t_data **data)
{
	if (*data == NULL)
		return ;
	if ((*data)->mlx != NULL)
	{
		if ((*data)->image.img != NULL)
			mlx_destroy_image((*data)->mlx, (*data)->image.img);
		free_textures(*data);
		if ((*data)->window != NULL)
			mlx_destroy_window((*data)->mlx, (*data)->window);
		mlx_destroy_display((*data)->mlx);
		free((*data)->mlx);
	}
	free_map(&(*data)->map);
	free(*data);
	*data = NULL;
}

static void	free_map(t_map *map)
{
	int	i;

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
	if (map->tx_door != NULL)
		free(map->tx_door);
	i = 0;
	while (i < SPRITE_COUNT)
	{
		if (&map->tx_sprite[i] != NULL)
			free(map->tx_sprite[i]);
		i++;
	}
	i = 0;
	while (map->data[i] != NULL) // !!!!!? && map->flags[i] != NULL
	{
		free(map->data[i]);
		free(map->info[i]);
		i++;
	}
	i = 0;
	free(map->data);
	free(map->info);
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
		if (data->tx_sprite[i].img != NULL)
			mlx_destroy_image(data->mlx, data->tx_sprite[i].img);
		i++;
	}
}
