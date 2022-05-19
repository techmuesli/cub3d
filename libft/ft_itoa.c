/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:06:34 by dbrandtn          #+#    #+#             */
/*   Updated: 2021/12/02 09:33:20 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	get_length_of_number(int num);
static void	convert_number(char *string, int *index, int num, int *min_int);

char	*ft_itoa(int n)
{
	char	*p;
	int		i;
	int		min_int;
	int		len;

	min_int = 0;
	len = get_length_of_number (n);
	p = ft_calloc (len + 1, sizeof (char));
	if (p == NULL)
		return (NULL);
	i = 0;
	if (n < 0)
	{
		if (n == -2147483648)
		{
			min_int = 1;
			n++;
		}
		p[i] = '-';
		n *= -1;
		i++;
	}
	convert_number (p, &i, n, &min_int);
	return (p);
}

static int	get_length_of_number(int num)
{
	int	len;

	if (num == 0)
		return (1);
	len = 0;
	if (num < 0)
		len++;
	while (num != 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

static void	convert_number(char *string, int *index, int num, int *min_int)
{
	int	digit;

	digit = num % 10;
	if (*min_int == 1)
	{
		digit++;
		*min_int = 0;
	}
	num /= 10;
	if (num != 0)
	{
		convert_number (string, index, num, min_int);
	}
	string[*index] = '0' + digit;
	(*index)++;
}
