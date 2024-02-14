/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:44:38 by aweissha          #+#    #+#             */
/*   Updated: 2024/02/14 12:30:48 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_think(t_data *data, t_philo *philo)
{
	if (dead_or_full(data) == 1)
		return (1);
	pthread_mutex_lock(&(data->print_mutex));
	if (dead_or_full(data) == 1)
	{
		pthread_mutex_unlock(&(data->print_mutex));
		return (1);
	}
	printf("%d %d is thinking\n", (int)(ft_time_ms() - data->start_time),
		philo->philo_number);
	pthread_mutex_unlock(&(data->print_mutex));
	return (0);
}

int	ft_sleep(t_data *data, t_philo *philo)
{
	if (dead_or_full(data) == 1)
		return (1);
	pthread_mutex_lock(&(data->print_mutex));
	if (dead_or_full(data) == 1)
	{
		pthread_mutex_unlock(&(data->print_mutex));
		return (1);
	}
	printf("%d %d is sleeping\n", (int)(ft_time_ms() - data->start_time),
		philo->philo_number);
	pthread_mutex_unlock(&(data->print_mutex));
	ft_sleep_ms(data->time_to_sleep);
	return (0);
}

void	*ft_philo(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (data->nb_philos == 1)
	{
		ft_sleep_ms(data->time_to_die);
		return (NULL);
	}
	if (((philo->philo_number) % 2) != 0)
		ft_sleep_ms(((data->time_to_eat) / 4));
	while (1)
	{
		if (ft_eat(data, philo) == 1)
			return (NULL);
		if (dead_or_full(data) == 1)
			return (NULL);
		if (ft_sleep(data, philo) == 1)
			return (NULL);
		if (ft_think(data, philo) == 1)
			return (NULL);
	}
}
