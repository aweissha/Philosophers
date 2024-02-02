/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_len_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:20:37 by aweissha          #+#    #+#             */
/*   Updated: 2023/10/20 10:46:18 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_len(int n, int *len)
{
	if (n == -2147483648)
	{
		ft_putstr_len("-2", len);
		n = 147483648;
	}
	if (n < 0)
	{
		ft_putchar_len_fd('-', len, 1);
		n = n * (-1);
	}
	if (n >= 10)
	{
		ft_putnbr_len(n / 10, len);
		if ((*len) != -1)
			ft_putchar_len_fd((n % 10) + '0', len, 1);
	}
	else
		if ((*len) != -1)
			ft_putchar_len_fd((n % 10) + '0', len, 1);
}

// int main(void)
// {
// 	int n;

// 	n = 123;
// 	ft_putnbr_fd(n, 1);
// }
