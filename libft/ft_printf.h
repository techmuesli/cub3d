/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:16:03 by dbrandtn          #+#    #+#             */
/*   Updated: 2022/02/07 12:22:09 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>

void	process_modifier_c(va_list *parguments, int *pchar_count);
void	process_modifier_s(va_list *parguments, int *pchar_count);
void	process_modifier_p(va_list *parguments, int *pchar_count);
void	process_modifier_d(va_list *parguments, int *pchar_count);
void	process_modifier_u(va_list *parguments, int *pchar_count);
void	process_modifier_x(va_list *parguments, int *pchar_count);
void	process_modifier_x2(va_list *parguments, int *pchar_count);

#endif
