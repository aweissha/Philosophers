/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:54:05 by aweissha          #+#    #+#             */
/*   Updated: 2024/02/02 12:54:09 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	time_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		ft_error("gettimeofday failed", EXIT_FAILURE);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
