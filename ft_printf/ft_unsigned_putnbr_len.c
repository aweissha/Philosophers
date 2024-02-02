/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_putnbr_len_fd.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:04:32 by aweissha          #+#    #+#             */
/*   Updated: 2023/10/20 10:50:05 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_unsigned_putnbr_len(unsigned int n, int *len)
{
	if (n >= 10)
	{
		ft_unsigned_putnbr_len(n / 10, len);
		if ((*len) != -1)
			ft_putchar_len_fd((n % 10) + '0', len, 1);
	}
	else
		if ((*len) != -1)
			ft_putchar_len_fd((n % 10) + '0', len, 1);
}
