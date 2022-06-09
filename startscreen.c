/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startscreen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:49:21 by dbrandtn          #+#    #+#             */
/*   Updated: 2022/06/09 13:49:24 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_startscreen(t_data *data)
{
	t_vec_i	screen;
	t_vec_i	tx;
	t_start	start;

	start = data->start;
	if (start.start_flag == 1)
	{
		tx.y = 0;
		screen.y = (SCREEN_HEIGHT / 2) - (START_HEIGHT / 2);
		while (screen.y < (SCREEN_HEIGHT / 2) + (START_HEIGHT / 2))
		{
			tx.x = 0;
			screen.x = (SCREEN_WIDTH / 2) - (START_WIDTH / 2);
			while (screen.x < (SCREEN_WIDTH / 2) + (START_WIDTH / 2))
			{
				if (start.start.data[tx.y * START_WIDTH + tx.x] != 0x0000FF)
					cub3d_mlx_pixel_put(&data->image, screen.x, screen.y, \
						start.start.data[tx.y * START_WIDTH + tx.x]);
				tx.x++;
				screen.x++;
			}
			tx.y++;
			screen.y++;
		}
	}
}
