/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:22:21 by dbrandtn          #+#    #+#             */
/*   Updated: 2021/12/13 09:45:55 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	str_len;

	if (s == NULL)
		return (NULL);
	str_len = ft_strlen (s);
	if (str_len <= start)
		len = 0;
	if (str_len - start < len)
		len = str_len - start;
	substring = malloc (len + 1);
	if (substring == NULL)
		return (NULL);
	ft_strlcpy (substring, &s[start], len + 1);
	return (substring);
}
