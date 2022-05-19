/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:18:41 by dbrandtn          #+#    #+#             */
/*   Updated: 2021/11/29 17:55:08 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	size_dst;
	size_t	size_src;

	size_src = ft_strlen (src);
	size_dst = ft_strlen (dst);
	if (dstsize == 0 || size_dst >= dstsize)
		return (size_src + dstsize);
	i = size_dst;
	j = 0;
	while (j < dstsize - size_dst - 1)
	{
		if (src[j] == '\0')
			break ;
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (size_dst + size_src);
}
