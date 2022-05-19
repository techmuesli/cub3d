/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:21:41 by dbrandtn          #+#    #+#             */
/*   Updated: 2021/11/30 12:57:22 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*copy;
	size_t	size;

	size = ft_strlen (s1);
	size++;
	copy = malloc (size);
	if (copy == NULL)
		return (NULL);
	ft_strlcpy (copy, s1, size);
	return (copy);
}
