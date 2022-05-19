/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 09:26:31 by dbrandtn          #+#    #+#             */
/*   Updated: 2021/12/20 09:46:06 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_length_of_number(unsigned int num);
static void	convert_number(char *string, int *index, unsigned int num);

char	*ft_utoa(unsigned int n)
{
	char	*p;
	int		i;
	int		len;

	len = get_length_of_number (n);
	p = ft_calloc (len + 1, sizeof (char));
	if (p == NULL)
		return (NULL);
	i = 0;
	convert_number (p, &i, n);
	return (p);
}

static int	get_length_of_number(unsigned int num)
{
	int	len;

	if (num == 0)
		return (1);
	len = 0;
	while (num != 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

static void	convert_number(char *string, int *index, unsigned int num)
{
	int	digit;

	digit = num % 10;
	num /= 10;
	if (num != 0)
	{
		convert_number (string, index, num);
	}
	string[*index] = '0' + digit;
	(*index)++;
}
