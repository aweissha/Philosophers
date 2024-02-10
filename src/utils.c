/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:54:05 by aweissha          #+#    #+#             */
/*   Updated: 2024/02/10 15:08:25 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_sleep_ms(long duration)
{
	long	start_time;

	start_time = ft_time_ms();
	while ((ft_time_ms() - start_time) < duration)
		usleep(100);
}

long	ft_time_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		ft_error("gettimeofday failed", EXIT_FAILURE);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
