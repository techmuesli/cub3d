/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:23:49 by dbrandtn          #+#    #+#             */
/*   Updated: 2021/12/01 11:32:35 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	*trim_beginning(const char *string, const char *set);
static char	*trim_end(const char *beginning, const char *set);
static char	*find_last_char(const char *string);
static int	is_part_of_set(char c, const char *set);

// size = end - start + 1 + 1 (\0)
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*end;
	char	*new;
	size_t	size;

	if (s1 == NULL || set == NULL)
		return (NULL);
	s1 = trim_beginning (s1, set);
	end = trim_end (s1, set);
	size = end - s1 + 2;
	if (*s1 == '\0')
		size = 1;
	new = malloc (size);
	if (new == NULL)
		return (NULL);
	ft_strlcpy (new, s1, size);
	return (new);
}

static char	*trim_beginning(const char *string, const char *set)
{
	while (*string != '\0')
	{
		if (is_part_of_set (*string, set) == 0)
			break ;
		string++;
	}
	return ((char *)string);
}

static char	*trim_end(const char *beginning, const char *set)
{
	char	*end;

	end = find_last_char (beginning);
	while (end > beginning)
	{
		if (is_part_of_set (*end, set) == 0)
			break ;
		end--;
	}
	return ((char *)end);
}

static char	*find_last_char(const char *string)
{
	while (*string != '\0')
		string++;
	string--;
	return ((char *)string);
}

static int	is_part_of_set(char c, const char *set)
{
	while (*set != '\0')
	{
		if (c == *set)
		{
			return (1);
		}
		set++;
	}
	return (0);
}
