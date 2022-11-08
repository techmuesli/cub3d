/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:47:17 by dbrandtn          #+#    #+#             */
/*   Updated: 2022/11/08 16:03:53 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	key_cb(int keycode, void *param);
int			mouse_cb(int x, int y, t_data *data);

// 17 = ON_DESTROY
void	set_up_hooks(void *window, t_data *data)
{
	mlx_hook(window, 2, 1, key_cb, data);
	mlx_hook(window, 6, (1L << 6), mouse_cb, data);
	mlx_hook(window, 17, 0, end_loop, data);
	mlx_loop_hook(data->mlx, run_loop, data);
}

// keycode 65307 = 'esc'
static int	key_cb(int keycode, void *param)
{
	t_data	*data;

	data = param;
	data->start_timer = 1;
	if (keycode == 65307)
		end_loop(param);
	else if (keycode == 65361)
		key_left(data);
	else if (keycode == 65363)
		key_right(data);
	else if (keycode == 119)
		key_w(data);
	else if (keycode == 97)
		key_a(data);
	else if (keycode == 115)
		key_s(data);
	else if (keycode == 100)
		key_d(data);
	else if (keycode == 102)
		key_f(data);
	return (0);
}

// data->rot_speed = 0.05 -> modified for "mouse sensitivity"
int	mouse_cb(int x, int y, t_data *data)
{
	(void)y;
	if (data->exit > 0)
		return (0);
	if (x < data->mouse_pos.x)
	{
		mlx_mouse_move(data->mlx, data->window, data->mouse_pos.x,
			data->mouse_pos.y);
		data->rot_speed = 0.05;
		key_left(data);
	}
	if (x > data->mouse_pos.x)
	{
		mlx_mouse_move(data->mlx, data->window, data->mouse_pos.x,
			data->mouse_pos.y);
		data->rot_speed = 0.05;
		key_right(data);
	}
	return (0);
}

int	end_loop(void *param)
{
	t_data	*data;

	data = param;
	mlx_loop_end(data->mlx);
	return (0);
}
