// !!!!!

#include "cub3d.h"

static void	free_map(t_map *map);

void	fdf_cleanup(t_data **data)
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
	i = 0;
	while (map->data[i] != NULL)
	{
		free(map->data[i]);
		i++;
	}
	free(map->data);
}
