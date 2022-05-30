// !!!!!

#include "cub3d.h"

void	display_result(t_data *data)
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
		if (data->user_name == NULL)
			ft_strlcpy(client.user_name, "unknown user", MAX_LEN);
		send_data(network, (char *)&client, sizeof(t_client_data));
		//mlx_set_font(data->mlx, data->window, char *name);
		//mlx_string_put(data->mlx, data->window, 50, 50, 0, "test output");
		recv_data(network);
	}
	network_cleanup(network);
}
