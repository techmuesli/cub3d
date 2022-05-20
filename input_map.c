// !!!!!

#include "cub3d.h"

static void	trim_line_end(char *line);
static int	*process_map_info(char *line, int *width);
static int	**init_map_data(t_vector *vec, int width);

int	load_map(t_data *data, char *line, int fd)
{
	int			width;
	int			max_width;
	int			*map_data;
	t_vector	*vec;

	max_width = 0;
	vec = vector_init(10, 10, 0);
	if (vec == NULL)
	{
		free(line);
		return (-1);
	}
	while (line != NULL)
	{
		trim_line_end(line);
		map_data = process_map_info(line, &width); // !!!!! check for fail
		vector_add(vec, map_data);
		if (width > max_width)
			max_width = width;
		free(line);
		line = get_next_line(fd);
	}
	data->map.x = max_width;
	data->map.y = vec->total;
	data->map.data = init_map_data(vec, max_width); // !!!!! check for fail
	vector_cleanup(vec);
	return (0);
}

static void	trim_line_end(char *line)
{
	int	len;

	if (line[0] == '\0')
		return ;
	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		line[len - 1] = '\0';
	str_trim_end(line);
}

static int	*process_map_info(char *line, int *total)
{
	int	i;
	int	*data;

	*total = ft_strlen(line) + 1;
	data = malloc(*total * sizeof(int));
	if (data == NULL)
		return (NULL);
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
			data[i] = MAP_TYPE_NOTHINGNESS;
		else if (line[i] == '0')
			data[i] = MAP_TYPE_EMPTY_SPACE;
		else if (line[i] == '1')
			data[i] = MAP_TYPE_WALL;
		else if (line[i] == 'N')
			data[i] = MAP_TYPE_N;
		else if (line[i] == 'E')
			data[i] = MAP_TYPE_E;
		else if (line[i] == 'S')
			data[i] = MAP_TYPE_S;
		else if (line[i] == 'W')
			data[i] = MAP_TYPE_W;
		else
			data[i] = MAP_TYPE_UNKNOWN;
		i++;
	}
	data[i] = MAP_END_OF_LINE;
	return (data);
}

static int	**init_map_data(t_vector *vec, int width)
{
	int	i;
	int	**map;

	map = ft_calloc(vec->total + 1, width * sizeof(int));
	if (map == NULL)
		return (NULL);
	i = 0;
	while (i < (int)vec->total)
	{
		map[i] = vector_get(vec, i);
		i++;
	}
	map[i] = NULL;
	vec->total = 0; // !!!!!
	return (map);
}
