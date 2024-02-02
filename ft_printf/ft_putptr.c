/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:01:35 by aweissha          #+#    #+#             */
/*   Updated: 2023/10/20 10:58:12 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putptr_hex_len(unsigned long long nbr, int *len)
{
	if (nbr >= 16)
	{
		ft_putptr_hex_len(nbr / 16, len);
		if ((*len) != -1)
			ft_putchar_len_fd("0123456789abcdef"[nbr % 16], len, 1);
	}
	else
		if ((*len) != -1)
			ft_putchar_len_fd("0123456789abcdef"[nbr % 16], len, 1);
}

void	ft_putptr(void *p, int *len)
{
	unsigned long long	n;	

	n = (unsigned long long)p;
	ft_putstr_len("0x", len);
	if ((*len) != -1)
		ft_putptr_hex_len(n, len);
}
