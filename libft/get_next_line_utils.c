/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:21:13 by dbrandtn          #+#    #+#             */
/*   Updated: 2022/01/28 11:45:13 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int		check_for_new_line(const char *string, int length);
char	**init_static(char **rest, int fd);
void	check_n_cleanup_static(char ***rest);

// if length == 0, check for '\0', otherwise check length
int	check_for_new_line(const char *string, int length)
{
	int	i;

	i = 1;
	if (length == 0)
	{
		while (*string != '\0')
		{
			if (*string == '\n')
				return (i);
			i++;
			string++;
		}
	}
	else
	{
		while (i <= length)
		{
			if (*string == '\n')
				return (i);
			i++;
			string++;
		}
	}
	return (0);
}

char	**init_static(char **rest, int fd)
{
	char	**buf;
	int		i;

	if (rest != NULL)
		return (rest);
	if (fd < 0 || fd >= 4096)
		return (NULL);
	buf = malloc (4096 * sizeof (char *));
	if (buf == NULL)
		return (NULL);
	i = 0;
	while (i < 4096)
	{
		buf[i] = NULL;
		i++;
	}
	return (buf);
}

void	check_n_cleanup_static(char ***rest)
{
	char	**tmp;
	int		i;

	tmp = *rest;
	i = 0;
	while (i < 4096)
	{
		if (tmp[i] != NULL)
			break ;
		i++;
	}
	if (i == 4096)
	{
		free (*rest);
		*rest = NULL;
	}
}
