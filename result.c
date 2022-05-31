// !!!!!

#include "cub3d.h"

static void	insert_top_score(t_data *data, t_server_data *server, int y_pos, int i)
{
	char	temp[1024];

	sprintf(temp, "# %d", i + 1);
	mlx_string_put(data->mlx, data->window, (SCREEN_WIDTH / 2) -200, y_pos,
		0xFFFFFF, temp);
	mlx_string_put(data->mlx, data->window, (SCREEN_WIDTH / 2), y_pos,
		0xFFFFFF, server->top[i].user_name);
	sprintf(temp, "%lu.%lus", server->top[i].time / 1000, server->top[i].time % 1000);
	mlx_string_put(data->mlx, data->window, (SCREEN_WIDTH / 2) + 200, y_pos,
		0xFFFFFF, temp);
}

static int	insert_current_score(t_data *data, t_server_data *server, t_client_data *client, int y_pos)
{
	char	temp[1024];
	int		rank;

	rank = server->rank;
	sprintf(temp, "# %d", rank);
	mlx_string_put(data->mlx, data->window, (SCREEN_WIDTH / 2) -200, y_pos,
		0xFF0000, temp);
	mlx_string_put(data->mlx, data->window, (SCREEN_WIDTH / 2), y_pos,
		0xFF0000, client->user_name);
	sprintf(temp, "%lu.%lus", client->time / 1000, client->time % 1000);
	mlx_string_put(data->mlx, data->window, (SCREEN_WIDTH / 2) + 200, y_pos,
		0xFF0000, temp);
	if (server->rank <= 10)
		return (1);
	return (0);
}

void	render_scoreboard(t_data *data, t_server_data *server, t_client_data *client)
{
	int		current;
	int		y_pos;
	int		i;

	mlx_mouse_show(data->mlx, data->window);
	// mlx_set_font(data->mlx, data->window, "lucidasanstypewriter-bold-24");
	mlx_set_font(data->mlx, data->window, "r24");
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
		y_pos += 50;
	}
	if (current == 0)
		insert_current_score(data, server, client, y_pos + 50);
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
		send_data(network, (char *)&client, sizeof(t_client_data));
		recv_data(data, network, &client);
	}
	network_cleanup(network);
}
