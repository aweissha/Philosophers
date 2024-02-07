/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:44:38 by aweissha          #+#    #+#             */
/*   Updated: 2024/02/07 17:39:31 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_think(t_data *data, t_philo *philo)
{
	long	timestamp;

	timestamp = ft_time_ms() - data->start_time;
	pthread_mutex_lock(data->mutex_print);
	if (data->someone_dead == 1 || data->someone_full == 1)
	{
		pthread_mutex_unlock(data->mutex_print);
		return (1);
	}
	printf("%ld %d is thinking\n", timestamp, philo->philo_number);
	pthread_mutex_unlock(data->mutex_print);
	return (0);
}

int	ft_sleep(t_data *data, t_philo *philo)
{
	long	timestamp;

	timestamp = ft_time_ms() - data->start_time;
	pthread_mutex_lock(data->mutex_print);
	if (data->someone_dead == 1 || data->someone_full == 1)
	{
		pthread_mutex_unlock(data->mutex_print);
		return (1);
	}
	printf("%ld %d is sleeping\n", timestamp, philo->philo_number);
	pthread_mutex_unlock(data->mutex_print);
	usleep((data->time_to_sleep) * 1000);
	return (0);
}

void	*ft_philo(void *arg)
{
	t_philo *philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;

	while (1)
	{
		if (ft_eat(data, philo) == 1)
			return (NULL);
		if (data->someone_dead == 1 || data->someone_full == 1)
			return (NULL);
		if (ft_sleep(data, philo) == 1)
			return (NULL);
		if (ft_think(data, philo) == 1)
			return (NULL);
	}
}
