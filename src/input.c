/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:47:53 by dbrandtn          #+#    #+#             */
/*   Updated: 2022/11/08 16:04:09 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	process_file_content(t_data *data, int fd);
static int	open_input_file(char *filename);

int	read_input_file(t_data *data, int level)
{
	char	*map;
	int		fd;

	map = create_map_file(level);
	if (map == NULL)
		return (-1);
	fd = open_input_file(map);
	if (fd < 0)
	{
		free(map);
		return (-1);
	}
	if (process_file_content(data, fd) != 0)
	{
		close(fd);
		remove(map);
		free(map);
		return (-1);
	}
	close(fd);
	remove(map);
	free(map);
	if (check_input(data) != 0)
		return (-1);
	return (0);
}

static int	open_input_file(char *filename)
{
	int	fd;

	// if (ft_strrcmp(filename, ".cub") != 0) !!!!!
	// 	return (-1);
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
				{
					free(line);
					return (-1);
				}
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

int	get_map_width(int *line)
{
	int	i;

	i = 0;
	while (line[i] != MAP_END_OF_LINE)
		i++;
	return (i);
}
