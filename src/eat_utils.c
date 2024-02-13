/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:40:57 by aweissha          #+#    #+#             */
/*   Updated: 2024/02/13 16:08:59 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_eat(t_data *data, t_philo *philo)
{
	if (take_forks_up(data, philo) == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	pthread_mutex_lock(&(data->print_mutex));
	if (dead_or_full(data) == 1)
	{
		pthread_mutex_unlock(&(data->print_mutex));
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	printf("%d %d is eating\n", (int)(ft_time_ms() - data->start_time),
		philo->philo_number);
	pthread_mutex_unlock(&(data->print_mutex));
	ft_sleep_ms(data->time_to_eat);
	put_forks_down(philo);
	return (0);
}

int	take_forks_up(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&(data->eating_mutex));
	philo->last_meal_time = ft_time_ms();
	(philo->number_eaten)++;
	pthread_mutex_unlock(&(data->eating_mutex));
	if (dead_or_full(data) == 1)
	{
		pthread_mutex_unlock(&(data->eating_mutex));
		return (1);
	}
	pthread_mutex_lock(&(data->print_mutex));
	printf("%d %d has taken a fork\n%d %d has taken a fork\n",
		(int)(ft_time_ms() - data->start_time), philo->philo_number,
		(int)(ft_time_ms() - data->start_time), philo->philo_number);
	pthread_mutex_unlock(&(data->print_mutex));
	return (0);
}

void	put_forks_down(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}
