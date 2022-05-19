/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:21:02 by dbrandtn          #+#    #+#             */
/*   Updated: 2022/03/01 17:11:58 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "get_next_line.h"

static char	*handle_eof(char ***rest, int bytes_read, int fd);
static int	read_next_block(int fd, char **rest);
static char	*prep_line(char **rest, int length);
static int	copy_buf_to_rest(char **rest, char *buf, int length);

char	*get_next_line(int fd)
{
	char		*line;
	int			len;
	static char	**rest;

	rest = init_static (rest, fd);
	if (rest == NULL)
		return (NULL);
	if (rest[fd] != NULL)
	{
		len = check_for_new_line (rest[fd], 0);
		if (len > 0)
		{
			line = prep_line (&rest[fd], len);
			return (line);
		}
	}
	len = read_next_block (fd, &rest[fd]);
	if (len <= 0)
	{
		line = handle_eof (&rest, len, fd);
		return (line);
	}
	len = check_for_new_line (rest[fd], 0);
	line = prep_line (&rest[fd], len);
	return (line);
}

static char	*handle_eof(char ***rest, int bytes_read, int fd)
{
	char	*line;
	char	**tmp;
	int		len;

	tmp = *rest;
	if (tmp[fd] != NULL)
	{
		if (bytes_read == 0)
		{
			len = ft_strlen (tmp[fd]);
			if (len != 0)
			{
				line = prep_line (&tmp[fd], len);
				return (line);
			}
		}
		free (tmp[fd]);
		tmp[fd] = NULL;
	}
	check_n_cleanup_static (rest);
	return (NULL);
}

// returns the number of bytes last read; -1 on error
static int	read_next_block(int fd, char **rest)
{
	char	*buf;
	int		len;
	int		bytes_read;

	buf = malloc (GNL_BUFFER_SIZE + 1);
	if (buf == NULL)
		return (-1);
	len = 0;
	while (len == 0)
	{
		bytes_read = read (fd, buf, GNL_BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free (buf);
			return (bytes_read);
		}
		if (copy_buf_to_rest (rest, buf, bytes_read) != 0)
		{
			free (buf);
			return (-1);
		}
		len = check_for_new_line (buf, bytes_read);
	}
	free (buf);
	return (bytes_read);
}

static int	copy_buf_to_rest(char **rest, char *buf, int length)
{
	char	*tmp;
	char	*copy;
	int		len_rest;

	len_rest = 0;
	if (*rest != NULL)
		len_rest = ft_strlen (*rest);
	tmp = *rest;
	*rest = malloc (len_rest + length + 1);
	if (*rest == NULL)
		return (-1);
	copy = *rest;
	if (tmp != NULL)
		ft_strlcpy (copy, tmp, len_rest + 1);
	buf[length] = '\0';
	ft_strlcpy (&copy[len_rest], buf, length + 1);
	if (tmp != NULL)
		free (tmp);
	return (0);
}

static char	*prep_line(char **rest, int length)
{
	char	*line;
	char	*tmp;
	int		len_rest;

	line = malloc (length + 1);
	if (line == NULL)
		return (NULL);
	ft_strlcpy (line, *rest, length + 1);
	len_rest = ft_strlen (*rest);
	tmp = *rest;
	*rest = malloc (len_rest - length + 1);
	if (*rest == NULL)
	{
		free (line);
		return (NULL);
	}
	ft_strlcpy (*rest, &tmp[length], len_rest - length + 1);
	free (tmp);
	return (line);
}
