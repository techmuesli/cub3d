/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   result.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:49:07 by dbrandtn          #+#    #+#             */
/*   Updated: 2022/11/08 16:04:32 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	insert_total_games(t_data *data, t_server_data *server, int y_pos)
{
	char	temp[MAX_LEN];

	sprintf(temp, "Total number of games: %d", server->num_of_games);
	mlx_string_put(data->mlx, data->window, (SCREEN_WIDTH / 2) - 100, y_pos,
		0x00FF00, temp);
}

static void	insert_top_score(t_data *data, t_server_data *server,
	int y_pos, int i)
{
	char	temp[1024];

	sprintf(temp, "# %d", i + 1);
	mlx_string_put(data->mlx, data->window, (SCREEN_WIDTH / 2) - 250, y_pos,
		0xFFFFFF, temp);
	sprintf(temp, "%.20s", server->top[i].user_name);
	mlx_string_put(data->mlx, data->window, (SCREEN_WIDTH / 2) - 50, y_pos,
		0xFFFFFF, temp);
#ifdef __linux__
	sprintf(temp, "%lu.%lus", server->top[i].time / 1000, server->top[i].time % 1000);
#elif __APPLE__
	sprintf(temp, "%llu.%llus", server->top[i].time / 1000, server->top[i].time % 1000);
#endif
	mlx_string_put(data->mlx, data->window, (SCREEN_WIDTH / 2) + 250, y_pos,
		0xFFFFFF, temp);
}

static int	insert_current_score(t_data *data, t_server_data *server,
	t_client_data *client, int y_pos)
{
	char	temp[1024];

	sprintf(temp, "# %d", server->rank);
	mlx_string_put(data->mlx, data->window, (SCREEN_WIDTH / 2) - 250, y_pos,
		0xFF0000, temp);
	sprintf(temp, "%.20s", client->user_name);
	mlx_string_put(data->mlx, data->window, (SCREEN_WIDTH / 2) - 50, y_pos,
		0xFF0000, temp);
#ifdef __linux__
	sprintf(temp, "%lu.%lus", client->time / 1000, client->time % 1000);
#elif __APPLE__
	sprintf(temp, "%llu.%llus", client->time / 1000, client->time % 1000);
#endif
	mlx_string_put(data->mlx, data->window, (SCREEN_WIDTH / 2) + 250, y_pos,
		0xFF0000, temp);
	return (1);
}

// mlx_set_font(data->mlx, data->window, "r24"); !!!!!
void	render_scoreboard(t_data *data, t_server_data *server,
	t_client_data *client)
{
	int		current;
	int		y_pos;
	int		i;

#ifdef __APPLE__
	mlx_set_font(data->mlx, data->window, "lucidasanstypewriter-bold-24");
#endif
	mlx_mouse_show(data->mlx, data->window);
	y_pos = 50;
	mlx_string_put(data->mlx, data->window, (SCREEN_WIDTH / 2) - 100, y_pos,
		0xFFFFFF, "Top 10 Maze Runners");
	current = 0;
	y_pos += 50;
	i = 0;
	while (i < server->num_of_games && i < 10)
	{
		if (server->rank == i + 1)
			current = insert_current_score(data, server, client, y_pos);
		else
			insert_top_score(data, server, y_pos, i);
		i++;
		y_pos += 40;
	}
	if (current == 0)
		insert_current_score(data, server, client, y_pos + 45);
	insert_total_games(data, server, y_pos + 90);
}

void	server_fetch(t_data *data)
{
	t_network		*network;
	t_client_data	client;	

	network = network_init("techmuesli.de");
	if (network == NULL)
		return ;
	if (connect_to_server(network) >= 0)
	{
		ft_bzero(&client, sizeof(t_client_data));
		client.time = get_time() - data->start.start_time;
		if (data->user_name == NULL || data->user_name[0] == '\0')
			ft_strlcpy(client.user_name, "unknown user", MAX_LEN);
		else
			ft_strlcpy(client.user_name, data->user_name, MAX_LEN);
		send(network->socket, (char *)&client, sizeof(t_client_data), 0);
		recv_data(data, network, &client);
	}
	network_cleanup(network);
}
