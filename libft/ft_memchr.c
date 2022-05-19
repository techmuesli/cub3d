/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:11:39 by dbrandtn          #+#    #+#             */
/*   Updated: 2021/11/29 10:51:44 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*string;

	string = s;
	while (n > 0)
	{
		if (*string == (unsigned char)c)
			return ((void *)string);
		string++;
		n--;
	}
	return (NULL);
}
