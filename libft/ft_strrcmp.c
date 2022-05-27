/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrcmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:40:54 by dbrandtn          #+#    #+#             */
/*   Updated: 2022/05/27 12:52:30 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	ft_strrcmp(const char *s1, const char *s2)
{
	int	max_compare;

	max_compare = ft_strlen(s1);
	if ((int)ft_strlen(s2) < max_compare)
		max_compare = ft_strlen(s2);
	while (*s1 != '\0')
		s1++;
	while (*s2 != '\0')
		s2++;
	while (*s1 == *s2)
	{
		if (max_compare == 0)
			break ;
		max_compare--;
		s1--;
		s2--;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
