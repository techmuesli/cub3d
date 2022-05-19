/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:15:14 by dbrandtn          #+#    #+#             */
/*   Updated: 2021/12/01 13:10:05 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	digit;

	if (n < 0)
	{
		if (n == -2147483648)
		{
			ft_putstr_fd ("-2147483648", fd);
			return ;
		}
		ft_putchar_fd ('-', fd);
		n *= -1;
	}
	digit = n % 10;
	n /= 10;
	if (n != 0)
		ft_putnbr_fd (n, fd);
	ft_putchar_fd ('0' + digit, fd);
}
