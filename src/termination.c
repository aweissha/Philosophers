/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termination.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:14:08 by aweissha          #+#    #+#             */
/*   Updated: 2024/02/13 16:15:06 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	dead_or_full(t_data *data)
{
	pthread_mutex_lock(&(data->termination_mutex));
	if (data->someone_dead == 1 || data->all_full == 1)
	{
		pthread_mutex_unlock(&(data->termination_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(data->termination_mutex));
	return (0);
}

int	check_all_full(t_data *data)
{
	int	number_eaten;
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_lock(&(data->eating_mutex));
		number_eaten = ((data->philos)[i]).number_eaten;
		pthread_mutex_unlock(&(data->eating_mutex));
		if (number_eaten < data->number_eat)
			break ;
		i++;
	}
	if (i == data->nb_philos)
	{
		pthread_mutex_lock(&(data->termination_mutex));
		data->all_full = 1;
		pthread_mutex_unlock(&(data->termination_mutex));
		pthread_mutex_lock(&(data->print_mutex));
		printf("%d Philosophers have eaten enough\n",
			(int)(ft_time_ms() - data->start_time));
		pthread_mutex_unlock(&(data->print_mutex));
		return (1);
	}
	return (0);
}

int	check_death(t_data *data)
{
	int		i;
	long	last_meal_time;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_lock(&(data->eating_mutex));
		last_meal_time = ((data->philos)[i]).last_meal_time;
		pthread_mutex_unlock(&(data->eating_mutex));
		if ((ft_time_ms() - last_meal_time) > (data->time_to_die))
		{
			pthread_mutex_lock(&(data->termination_mutex));
			data->someone_dead = 1;
			pthread_mutex_unlock(&(data->termination_mutex));
			pthread_mutex_lock(&(data->print_mutex));
			printf("%d Philosopher %d died of starvation\n",
				(int)(ft_time_ms() - data->start_time),
				((data->philos)[i]).philo_number);
			pthread_mutex_unlock(&(data->print_mutex));
			return (1);
		}
		i++;
	}
	return (0);
}

void	*termination_checker(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_death(data) == 1)
			return (NULL);
		if (data->number_eat > 0 && check_all_full(data) == 1)
			return (NULL);
		usleep(100);
	}
	return (NULL);
}
