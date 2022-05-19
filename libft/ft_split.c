/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:24:50 by dbrandtn          #+#    #+#             */
/*   Updated: 2021/11/30 16:55:50 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	get_substring_count(const char *string, char c);
static int	fill_array(char **array, const char *str, char c);
static int	copy_data_if_needed(char **array, int *idx, const char *str,
				int length);

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		substring_count;

	if (s == NULL)
		return (NULL);
	substring_count = get_substring_count (s, c);
	array = ft_calloc (substring_count + 1, sizeof (char *));
	if (array == NULL)
		return (NULL);
	if (fill_array (array, s, c) != 0)
		return (NULL);
	return (array);
}

static int	get_substring_count(const char *string, char c)
{
	int	count;
	int	len;

	count = 0;
	len = 0;
	while (*string != '\0')
	{
		if (*string == c)
		{
			if (len != 0)
				count++;
			len = 0;
		}
		else
		{
			len++;
		}
		string++;
	}
	if (len != 0)
		count++;
	return (count);
}

static int	fill_array(char **array, const char *str, char c)
{
	int	i;
	int	length;

	i = 0;
	length = 0;
	while (*str != '\0')
	{
		if (*str == c)
		{
			if (copy_data_if_needed (array, &i, str, length) != 0)
				return (1);
			length = 0;
		}
		else
		{
			length++;
		}
		str++;
	}
	if (copy_data_if_needed (array, &i, str, length) != 0)
		return (1);
	array[i] = NULL;
	return (0);
}

static int	copy_data_if_needed(char **array, int *idx, const char *str,
	int length)
{
	int	j;

	j = 0;
	if (length != 0)
	{
		array[*idx] = malloc (length + 1);
		if (array[*idx] == NULL)
		{
			while (array[j] != NULL)
			{
				free (array[j]);
				j++;
			}
			free (array);
			return (1);
		}
		ft_strlcpy (array[*idx], &str[-length], length + 1);
		(*idx)++;
	}
	return (0);
}
