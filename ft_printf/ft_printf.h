/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:50:21 by aweissha          #+#    #+#             */
/*   Updated: 2023/10/20 10:57:05 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

int		ft_printf(const char *string, ...);
void	ft_putptr(void *p, int *len);
void	ft_unsigned_putnbr_len(unsigned int n, int *len);
void	ft_putnbr_hex_len(unsigned int nbr, int *len);
void	ft_putnbr_hex_upper_len(unsigned int nbr, int *len);
void	ft_putchar_len_fd(int c, int *len, int fd);
void	ft_putnbr_len(int n, int *len);
void	ft_putstr_len(char *s, int *len);

#endif
