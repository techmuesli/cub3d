/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_mod_hex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 11:32:13 by dbrandtn          #+#    #+#             */
/*   Updated: 2022/01/27 14:35:03 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include "ft_printf.h"

static void	print_ull_as_hex_value(unsigned long long ull, int *pchar_count);
static void	print_ui_as_hex_value(unsigned int ui, int *pchar_count,
				int upper_case);

void	process_modifier_p(va_list *parguments, int *pchar_count)
{
	unsigned long long	ull;

	ull = va_arg (*parguments, unsigned long long);
	print_ull_as_hex_value (ull, pchar_count);
}

static void	print_ull_as_hex_value(unsigned long long ull, int *pchar_count)
{
	int	modulo;

	modulo = ull % 16;
	ull /= 16;
	if (ull > 0)
	{
		print_ull_as_hex_value (ull, pchar_count);
	}
	else
	{
		ft_putchar_fd ('0', FD_STDOUT);
		ft_putchar_fd ('x', FD_STDOUT);
		(*pchar_count) += 2;
	}
	if (modulo >= 0 && modulo <= 9)
	{
		ft_putchar_fd ('0' + modulo, FD_STDOUT);
	}
	else
	{
		ft_putchar_fd ('a' + (modulo - 10), FD_STDOUT);
	}
	(*pchar_count)++;
}

void	process_modifier_x(va_list *parguments, int *pchar_count)
{
	unsigned int	ui;

	ui = va_arg (*parguments, unsigned int);
	print_ui_as_hex_value (ui, pchar_count, 0);
}

void	process_modifier_x2(va_list *parguments, int *pchar_count)
{
	unsigned int	ui;

	ui = va_arg (*parguments, unsigned int);
	print_ui_as_hex_value (ui, pchar_count, 1);
}

static void	print_ui_as_hex_value(unsigned int ui, int *pchar_count,
				int upper_case)
{
	int	modulo;

	modulo = ui % 16;
	ui /= 16;
	if (ui > 0)
		print_ui_as_hex_value (ui, pchar_count, upper_case);
	if (modulo >= 0 && modulo <= 9)
	{
		ft_putchar_fd ('0' + modulo, FD_STDOUT);
	}
	else
	{
		if (upper_case == 0)
			ft_putchar_fd ('a' + (modulo - 10), FD_STDOUT);
		else
			ft_putchar_fd ('A' + (modulo - 10), FD_STDOUT);
	}
	(*pchar_count)++;
}
