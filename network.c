// !!!!!

#include "cub3d.h"

static int	dns_look_up(t_network *network, char *domain_name);

t_network	*network_init(char *domain_name)
{
	t_network	*network;

	network = ft_calloc(1, sizeof(t_network));
	if (network == NULL)
		return (NULL);
	network->socket = socket(AF_INET, SOCK_STREAM, 0);
	if (network->socket < 0)
	{
		free(network);
		return (NULL);
	}
	ft_bzero(&network->server, sizeof(struct sockaddr_in));
	if (dns_look_up(network, domain_name) != 0)
	{
		free(network);
		return (NULL);
	}
	network->server.sin_family = AF_INET;
	network->server.sin_port = htons(PORT);
	return (network);
}

void	network_cleanup(t_network *network)
{
	if (network == NULL)
		return ;
	close(network->socket);
	free(network);
}

int	connect_to_server(t_network *network)
{
	if (connect(network->socket, (struct sockaddr *)&network->server,
			sizeof(network->server)) < 0)
		return (-1);
	return (0);
}

int	send_data(t_network *network, char *data, size_t size)
{
	if (send(network->socket, data, size, 0) != (int)size)
		return (-1);
	return (0);
}

int	recv_data(t_data *data, t_network *network, t_client_data *client)
{
	char			buf[BUFSIZE];
	int				i;
	int				size;
	t_server_data	*server;

	size = recv(network->socket, buf, BUFSIZE, 0);
	if (size <= 0)
		return (-1);
	server = (t_server_data *)buf;
	printf("Number of total games: %d\n", server->num_of_games);
	i = 0;
	while (i < server->num_of_games && i < 10)
	{
		printf("%d. %s - %llu\n", i + 1, server->top[i].user_name, server->top[i].time);
		i++;
	}
	render_scoreboard(data, server, client);
	return (0);
}

static int	dns_look_up(t_network *network, char *domain_name)
{
	struct hostent	*host_info;

	host_info = gethostbyname(domain_name);
	if (host_info == NULL || host_info->h_addr_list[0] == NULL)
		return (-1);
	ft_memcpy(&network->server.sin_addr, host_info->h_addr_list[0],
		host_info->h_length);
	return (0);
}
