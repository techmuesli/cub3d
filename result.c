// !!!!!

#include "cub3d.h"

void	render_scoreboard(t_data *data)
{
	char	*info;

	mlx_set_font(data->mlx, data->window, "lucidasanstypewriter-bold-24");
	info = "Please enter your name >_";
	mlx_string_put(data->mlx, data->window, (SCREEN_WIDTH / 2) - 27, SCREEN_HEIGHT / 2, 0xFFFFFF, \
		info);
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
		recv_data(data, network);
	}
	network_cleanup(network);
}
