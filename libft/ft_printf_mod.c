/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_mod.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 11:36:53 by dbrandtn          #+#    #+#             */
/*   Updated: 2022/06/09 13:50:51 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include "ft_printf.h"

static int	get_length_of_number(int num);

// char is promoted to int
void	process_modifier_c(va_list *parguments, int *pchar_count)
{
	char	c;

	c = va_arg (*parguments, int);
	ft_putchar_fd (c, FD_STDOUT);
	(*pchar_count)++;
}

void	process_modifier_s(va_list *parguments, int *pchar_count)
{
	char	*p;

	p = va_arg (*parguments, char *);
	if (p != NULL)
	{
		ft_putstr_fd (p, FD_STDOUT);
		(*pchar_count) += ft_strlen (p);
	}
	else
	{
		ft_putstr_fd ("(null)", FD_STDOUT);
		(*pchar_count) += 6;
	}
}

void	process_modifier_d(va_list *parguments, int *pchar_count)
{
	int		n;

	n = va_arg (*parguments, int);
	ft_putnbr_fd(n, FD_STDOUT);
	(*pchar_count) += get_length_of_number(n);
}

void	process_modifier_u(va_list *parguments, int *pchar_count)
{
	int		ui;

	ui = va_arg (*parguments, unsigned int);
	ft_put_uint_fd(ui, FD_STDOUT);
	(*pchar_count) += get_length_of_number(ui);
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
