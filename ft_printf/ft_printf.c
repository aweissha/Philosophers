/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:36:58 by aweissha          #+#    #+#             */
/*   Updated: 2023/10/20 11:27:31 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	check_keyword(const char s, va_list args, int *len)
{
	if (s == 'c')
		ft_putchar_len_fd(va_arg(args, int), len, 1);
	else if (s == 's')
		ft_putstr_len(va_arg(args, char *), len);
	else if (s == 'p')
		ft_putptr(va_arg(args, void *), len);
	else if (s == 'd' || s == 'i')
		ft_putnbr_len(va_arg(args, int), len);
	else if (s == 'u')
		ft_unsigned_putnbr_len(va_arg(args, unsigned int), len);
	else if (s == 'x')
		ft_putnbr_hex_len(va_arg(args, unsigned int), len);
	else if (s == 'X')
		ft_putnbr_hex_upper_len(va_arg(args, unsigned int), len);
	else if (s == '%')
		ft_putchar_len_fd('%', len, 1);
}

int	ft_printf(const char *string, ...)
{
	va_list			args;
	int				i;
	int				len;

	len = 0;
	va_start(args, string);
	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '%')
		{
			check_keyword(string[i + 1], args, &len);
			i++;
		}
		else
			ft_putchar_len_fd(string[i], &len, 1);
		i++;
		if (len == -1)
			break ;
	}
	va_end(args);
	return (len);
}

// #include <stdio.h>
// int	main(void)
// {
	// printf("real printf:");
	// printf("\001\002\007\v\010\f\r\n");
	// printf("\n");
// 	printf("my printf:");
// 	ft_printf("\001\002\007\v\010\f\r\n");
// }
