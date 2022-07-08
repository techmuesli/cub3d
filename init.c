/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:47:25 by dbrandtn          #+#    #+#             */
/*   Updated: 2022/07/08 11:26:03 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	init_image(t_data *data, int width, int height);
static void	general_init(t_data *data, char *user_name);

t_data	*cub3d_init(int width, int height, char *title, char *user_name)
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
		cub3d_cleanup(&data);
		return (NULL);
	}
	if (init_image(data, width, height) != 0)
	{
		cub3d_cleanup(&data);
		return (NULL);
	}
	mlx_mouse_hide(data->mlx, data->window);
	general_init(data, user_name);
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

static void	init_startscreen(t_data *data)
{
	t_vec_i	size;

	size.x = START_WIDTH;
	size.y = START_HEIGHT;
	data->start.start_flag = 1;
	data->start.start.img = mlx_xpm_file_to_image(data->mlx,
			"./textures/start_screen.xpm", &size.x, &size.y);
	if (data->start.start.img == NULL)
		data->start.start_flag = 0;
	else
		data->start.start.data = \
			(int *)mlx_get_data_addr(data->start.start.img,
				&data->start.start.bpp, &data->start.start.size_line,
				&data->start.start.endian);
}

static void	general_init(t_data *data, char *user_name)
{
	if (user_name != NULL)
	{
		user_name[MAX_LEN - 1] = '\0';
		data->user_name = ft_strdup(user_name);
	}
	set_up_hooks(data->window, data);
	data->map.flr.r = -1;
	data->map.flr.g = -1;
	data->map.flr.b = -1;
	data->map.ceiling.r = -1;
	data->map.ceiling.g = -1;
	data->map.ceiling.b = -1;
	data->mouse_pos.x = SCREEN_WIDTH / 2;
	data->mouse_pos.y = SCREEN_HEIGHT / 2;
	data->level = LEVEL_1;
	init_startscreen(data);
}
