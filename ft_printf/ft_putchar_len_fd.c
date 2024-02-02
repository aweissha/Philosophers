/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_len_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:46:21 by aweissha          #+#    #+#             */
/*   Updated: 2023/10/18 15:48:06 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar_len_fd(int c, int *len, int fd)
{
	if (write(fd, &c, 1) == -1)
		(*len) = -1;
	else
		(*len)++;
}
// int main(void)
// {
// 	ft_putchar_fd('z', 1);
// }
