/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_uint_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 13:58:37 by dbrandtn          #+#    #+#             */
/*   Updated: 2022/01/28 14:01:16 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_put_uint_fd(unsigned int ui, int fd)
{
	int	digit;

	digit = ui % 10;
	ui /= 10;
	if (ui != 0)
		ft_put_uint_fd (ui, fd);
	ft_putchar_fd ('0' + digit, fd);
}
