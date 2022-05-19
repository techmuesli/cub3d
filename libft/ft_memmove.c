/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:11:02 by dbrandtn          #+#    #+#             */
/*   Updated: 2021/12/01 11:20:55 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static void	copy_forward(char *dest, const char *source, size_t len);
static void	copy_backwards(char *dest, const char *source, size_t len);

// copy backwards if dst > src - to protect against overlapping
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dest;
	const char	*source;

	if (dst == NULL && src == NULL)
		return (NULL);
	dest = dst;
	source = src;
	if (dst < src)
		copy_forward (dest, source, len);
	else
		copy_backwards (dest, source, len);
	return (dst);
}

static void	copy_forward(char *dest, const char *source, size_t len)
{
	size_t		i;

	i = 0;
	while (i < len)
	{
		dest[i] = source[i];
		i++;
	}
}

static void	copy_backwards(char *dest, const char *source, size_t len)
{
	while (len > 0)
	{
		dest[len - 1] = source[len - 1];
		len--;
	}
}
