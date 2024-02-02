/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex_upper_len_fd.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:08:27 by aweissha          #+#    #+#             */
/*   Updated: 2023/10/20 10:55:01 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_hex_upper_len(unsigned int nbr, int *len)
{
	if (nbr < 0)
	{
		ft_putchar_len_fd('-', len, 1);
		nbr = nbr * (-1);
	}
	if (nbr >= 16)
	{
		ft_putnbr_hex_upper_len(nbr / 16, len);
		if ((*len) != -1)
			ft_putchar_len_fd("0123456789ABCDEF"[nbr % 16], len, 1);
	}
	else
		if ((*len) != -1)
			ft_putchar_len_fd("0123456789ABCDEF"[nbr % 16], len, 1);
}
