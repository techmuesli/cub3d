/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:15:48 by dbrandtn          #+#    #+#             */
/*   Updated: 2022/02/07 12:13:01 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"
#include "libft.h"

static void	run_conversion(char *string, int *pchar_count,
				va_list *parguments);
static void	run_modifier_func(char modifier, int *pchar_count,
				va_list *parguments);

int	ft_printf(const char *format, ...)
{
	int		char_count;
	va_list	arguments;

	va_start (arguments, format);
	char_count = 0;
	while (*format != '\0')
	{
		if (*format == '%')
		{
			run_conversion ((char *)format, &char_count, &arguments);
			format++;
		}
		else
		{
			ft_putchar_fd (*format, FD_STDOUT);
			char_count++;
		}
		if (*format != '\0')
			format++;
	}
	va_end (arguments);
	return (char_count);
}

static void	run_conversion(char *string, int *pchar_count,
				va_list *parguments)
{
	string++;
	if (*string == '%')
	{
		ft_putchar_fd (*string, FD_STDOUT);
		(*pchar_count)++;
	}
	else
	{
		run_modifier_func (*string, pchar_count, parguments);
	}
}

static void	run_modifier_func(char modifier, int *pchar_count,
				va_list *parguments)
{
	if (modifier == 'c')
		process_modifier_c (parguments, pchar_count);
	else if (modifier == 's')
		process_modifier_s (parguments, pchar_count);
	else if (modifier == 'p')
		process_modifier_p (parguments, pchar_count);
	else if (modifier == 'd' || modifier == 'i')
		process_modifier_d (parguments, pchar_count);
	else if (modifier == 'u')
		process_modifier_u (parguments, pchar_count);
	else if (modifier == 'x')
		process_modifier_x (parguments, pchar_count);
	else if (modifier == 'X')
		process_modifier_x2 (parguments, pchar_count);
}
