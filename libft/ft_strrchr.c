/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:19:55 by dbrandtn          #+#    #+#             */
/*   Updated: 2021/11/26 15:20:11 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strrchr(const char *s, int c)
{
	const char	*end;

	end = s;
	while (*end != '\0')
		end++;
	if (*end == (char)c)
		return ((char *)end);
	end--;
	while (end >= s)
	{
		if (*end == (char)c)
			return ((char *)end);
		end--;
	}
	return (NULL);
}
