// !!!!!

#include "cub3d.h"

static int	process_file_content(t_data *data, int fd);
static int	open_input_file(char *filename);

int	read_input_file(t_data *data, char *filename)
{
	int		fd;

	fd = open_input_file(filename);
	if (fd < 0)
		return (-1);
	if (process_file_content(data, fd) != 0)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	if (check_input(data) != 0)
		return (-1);
	return (0);
}

static int	open_input_file(char *filename)
{
	int	fd;

	if (ft_strnstr(filename, ".cub", ft_strlen(filename)) == NULL) // !!!!! TODO
		return (-1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	return (fd);
}

static int	process_file_content(t_data *data, int fd)
{
	char	*line;
	int		type;

	line = get_next_line(fd);
	while (line != NULL)
	{
		type = get_type_identifier(line);
		if (type != INFO_TYPE_EMPTY)
		{
			if (type == INFO_TYPE_MAP)
			{
				if (load_map(data, line, fd) != 0)
					return (-1);
				return (0);
			}
			if (get_type_info(&data->map, line, type) != 0)
				return (-1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}
