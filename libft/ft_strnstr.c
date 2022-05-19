/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:21:04 by dbrandtn          #+#    #+#             */
/*   Updated: 2021/12/13 10:43:14 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	if (*needle == '\0')
		return ((char *)haystack);
	i = 0;
	while (*haystack != '\0' && len > 0)
	{
		if (*haystack == *needle)
		{
			i = 0;
			while (haystack[i] == needle[i] && i < len)
			{
				i++;
				if (needle[i] == '\0')
					return ((char *)haystack);
				if (haystack[i] == '\0')
					return (NULL);
			}
		}
		haystack++;
		len--;
	}
	return (NULL);
}
