/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_len_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:04:19 by aweissha          #+#    #+#             */
/*   Updated: 2023/10/20 10:43:32 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr_len(char *s, int *len)
{
	unsigned int	i;

	i = 0;
	if (s == NULL)
	{
		if (write (1, "(null)", 6) == -1)
			(*len) = -1;
		else
			(*len) += 6;
	}
	else
	{
		while (s[i] != '\0')
		{
			ft_putchar_len_fd(s[i], len, 1);
			i++;
			if ((*len) == -1)
				break ;
		}
	}
}
// int main(void)
// {
// 	char s[] = "blablabla";
// 	ft_putstr_fd(s, 1);
// }
