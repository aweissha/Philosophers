/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:40:57 by aweissha          #+#    #+#             */
/*   Updated: 2024/02/06 18:08:35 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_eat(t_data *data, t_philo *philo)
{
	long	timestamp;

	take_forks_up(philo);

	timestamp = ft_time_ms() - data->start_time;
	pthread_mutex_lock(data->mutex_print);
	printf("%ld %d is eating\n", timestamp, philo->philo_number);
	pthread_mutex_unlock(data->mutex_print);
	usleep((data->time_to_eat) * 1000);
	put_forks_down(philo);
}

void	take_forks_up(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork_mutex);
	pthread_mutex_lock(philo->left_fork_mutex);
	printf("status ok\n");
	sleep(3);
	(*(philo->right_fork))--;
	(*(philo->left_fork))--;

}

void	put_forks_down(t_philo *philo)
{
	(*(philo->right_fork))++;
	(*(philo->left_fork))++;
	pthread_mutex_unlock(philo->right_fork_mutex);
	pthread_mutex_unlock(philo->left_fork_mutex);
}
