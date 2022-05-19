/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:22:48 by dbrandtn          #+#    #+#             */
/*   Updated: 2021/11/30 16:47:16 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_string;
	size_t	s1_length;
	size_t	new_length;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_length = ft_strlen (s1);
	new_length = s1_length + ft_strlen (s2);
	new_length++;
	new_string = malloc (new_length);
	if (new_string == NULL)
		return (NULL);
	ft_strlcpy (new_string, s1, new_length);
	ft_strlcpy (&new_string[s1_length], s2, new_length);
	return (new_string);
}
