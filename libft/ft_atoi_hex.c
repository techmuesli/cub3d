/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 16:35:35 by dbrandtn          #+#    #+#             */
/*   Updated: 2022/02/16 16:51:44 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_hex(char c);

int	ft_atoi_hex(const char *str)
{
	int	value;

	while (*str == '\t' || *str == '\n' || *str == '\v' || *str == '\f'
		|| *str == '\r' || *str == ' ')
		str++;
	if (*str == '0')
		str++;
	if (*str == 'x' || *str == 'X')
		str++;
	value = 0;
	while (is_hex(*str) == 1)
	{
		value *= 16;
		if (*str >= '0' && *str <= '9')
			value += (*str - '0');
		else if (*str >= 'a' && *str <= 'f')
			value += (*str - 'a' + 10);
		else if (*str >= 'A' && *str <= 'F')
			value += (*str - 'A' + 10);
		str++;
	}
	return (value);
}

static int	is_hex(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	if (c >= 'a' && c <= 'f')
		return (1);
	if (c >= 'A' && c <= 'F')
		return (1);
	return (0);
}
