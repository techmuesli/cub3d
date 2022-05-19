// !!!!!

#include "cub3d.h"

static int		process_line(t_map *map, char *line, int line_num);
static int		init_map(t_map *map, char *filename);
static int		get_file_dimensions(t_map *map, char *filename);

int	read_input_file(t_data *data, char *filename)
{
	char	*line;
	int		fd;
	int		line_num;

	if (ft_strnstr(filename, ".cub", ft_strlen(filename)) == NULL) // !!!!! TODO
		return (-1);
	if (init_map(&data->map, filename) != 0)
		return (-1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	line_num = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		process_line(&data->map, line, line_num);
		line_num++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (check_input(data) != 0)
		return (-1);
	return (0);
}

static int	process_line(t_map *map, char *line, int line_num)
{
	int	i;
	int	value;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] == ' ')
			value = -1;
		else if (line[i] == '0')
			value = 0;
		else if (line[i] == '1')
			value = 1;
		else // !!!!! N, S, E, W
			value = 2;
		map->data[line_num][i] = value;
		i++;
	}
	while (i < map->x)
	{
		map->data[line_num][i] = -1;
		i++;
	}
	return (0);
}

static int	init_map(t_map *map, char *filename)
{
	int		i;

	if (get_file_dimensions(map, filename) != 0)
		return (-1);
	map->data = ft_calloc(map->y, sizeof(int *));
	if (map == NULL)
		return (-1);
	i = 0;
	while (i < map->y)
	{
		map->data[i] = ft_calloc(map->x, sizeof(int));
		if (map->data[i] == NULL)
			return (-1);
		i++;
	}
	return (0);
}

static int	get_file_dimensions(t_map *map, char *filename)
{
	char	*line;
	int		fd;

	map->x = 0;
	map->y = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		map->y++;
		if ((int)ft_strlen(line) > map->x)
			map->x = ft_strlen(line); // !!!!! '\n' ?
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
