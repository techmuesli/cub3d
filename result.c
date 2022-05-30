// !!!!!

#include "cub3d.h"

void	render_scoreboard(t_data *data, t_server_data *server, t_client_data *client)
{
	char	*info;
	int		y_pos;
	int		i;
	char	*time;

	mlx_set_font(data->mlx, data->window, "lucidasanstypewriter-bold-24");
	info = "Please enter your name >_";
	// start at the top of the screen
	y_pos = 50;
	mlx_string_put(data->mlx, data->window, (SCREEN_WIDTH / 2) - 27, y_pos, 0xFFFFFF, \
		"Top 10 Maze Runners");

	i = 0;
	while (i < server->num_of_games && i < 10)
	{
		mlx_string_put(data->mlx, data->window, (SCREEN_WIDTH / 2) - 100, y_pos, 0xFFFFFF, \
		server->top[i].rank);
		mlx_string_put(data->mlx, data->window, (SCREEN_WIDTH / 2), y_pos, 0xFFFFFF, \
		server->top[i].user_name);
		time = sprintf("%llu", server->top[i].time);
		mlx_string_put(data->mlx, data->window, (SCREEN_WIDTH / 2) + 100, y_pos, 0xFFFFFF, \
		time);
		free(time);
		// place | name | time
		i++;
		y_pos += 20;
	}

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
		recv_data(data, network, client);
	}
	network_cleanup(network);
}
