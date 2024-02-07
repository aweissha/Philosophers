/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:40:57 by aweissha          #+#    #+#             */
/*   Updated: 2024/02/07 17:35:30 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_eat(t_data *data, t_philo *philo)
{
	long	timestamp;

	if (take_forks_up(data, philo) == 1)
	{
		pthread_mutex_unlock(philo->right_fork_mutex);
		pthread_mutex_unlock(philo->left_fork_mutex);
		return (1);
	}
	timestamp = ft_time_ms() - data->start_time;
	pthread_mutex_lock(data->mutex_print);
	printf("%ld %d is eating\n", timestamp, philo->philo_number);
	pthread_mutex_unlock(data->mutex_print);
	philo->last_meal_time = ft_time_ms();
	usleep((data->time_to_eat) * 1000);
	(philo->number_eaten)++;
	if (put_forks_down(data, philo) == 1)
		return (1);
	return (0);
}

int	take_forks_up(t_data *data, t_philo *philo)
{
	long	timestamp;

	pthread_mutex_lock(philo->right_fork_mutex);
	pthread_mutex_lock(philo->left_fork_mutex);
	(*(philo->right_fork))--;
	(*(philo->left_fork))--;
	timestamp = ft_time_ms() - data->start_time;
	pthread_mutex_lock(data->mutex_print);
	if (data->someone_dead == 1 || data->someone_full == 1)
	{
		pthread_mutex_unlock(data->mutex_print);	
		return (1);
	}
	printf("%ld %d has taken forks\n", timestamp, philo->philo_number);
	pthread_mutex_unlock(data->mutex_print);
	return (0);
}

int	put_forks_down(t_data *data, t_philo *philo)
{
	long	timestamp;
		
	(*(philo->right_fork))++;
	(*(philo->left_fork))++;
	timestamp = ft_time_ms() - data->start_time;
	pthread_mutex_lock(data->mutex_print);
	if (data->someone_dead == 1 || data->someone_full == 1)
	{
		pthread_mutex_unlock(data->mutex_print);
		pthread_mutex_unlock(philo->right_fork_mutex);
		pthread_mutex_unlock(philo->left_fork_mutex);
		return (1);
	}
	printf("%ld %d has put down forks\n", timestamp, philo->philo_number);
	pthread_mutex_unlock(data->mutex_print);
	pthread_mutex_unlock(philo->right_fork_mutex);
	pthread_mutex_unlock(philo->left_fork_mutex);
	return (0);
}
