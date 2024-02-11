/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:43:18 by aweissha          #+#    #+#             */
/*   Updated: 2024/02/11 14:35:10 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*ft_termination_checker(void *arg)
{
	t_data	*data;
	int		i;
	long	last_meal_time;
	int		number_eaten;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		pthread_mutex_lock(&(data->eating_mutex));
		while (i < data->number_philos)
		{
			last_meal_time = ((data->philos)[i]).last_meal_time;
			if ((ft_time_ms() - last_meal_time) > (data->time_to_die))
			{
				data->someone_dead = 1;
				pthread_mutex_lock(&(data->print_mutex));
				printf("Philosopher %d died of starvation\n", ((data->philos)[i]).philo_number);
				pthread_mutex_unlock(&(data->print_mutex));
				pthread_mutex_unlock(&(data->eating_mutex));	
				return (NULL);
			}
			if (data->number_eat >= 0)
			{
				number_eaten = ((data->philos)[i]).number_eaten;
				if (number_eaten >= data->number_eat)
				{
					data->someone_full = 1;
					pthread_mutex_lock(&(data->print_mutex));
					printf("Philosopher %d has eaten enough\n", ((data->philos)[i]).philo_number);
					pthread_mutex_unlock(&(data->print_mutex));
					pthread_mutex_unlock(&(data->eating_mutex));
					return (NULL);
				}
			}
			i++;
		}
		pthread_mutex_unlock(&(data->eating_mutex));
		usleep(100);
	}
	return (NULL);
}

int	ft_create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_philos)
	{
		data->philos[i].philo_index = i;
		data->philos[i].philo_number = i + 1;
		data->philos[i].right_fork_mutex = &((data->fork_mutexes)[i]);
		data->philos[i].number_eaten = 0;
		data->philos[i].data = data;
		if (i > 0)
			data->philos[i].left_fork_mutex = &((data->fork_mutexes)[i - 1]);
		else
			data->philos[i].left_fork_mutex = &((data->fork_mutexes)[(data->number_philos) - 1]);
		i++;
	}
	data->start_time = ft_time_ms();
	i = 0;
	while (i < data->number_philos)
	{
		((data->philos)[i]).last_meal_time = ft_time_ms();
		if (pthread_create(&((data->philo_threads)[i]), NULL, &ft_philo, &((data->philos)[i])) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&(data->termination_checker), NULL, &ft_termination_checker, data) != 0)
		return (1);
	return (0);
}

int	ft_init_data(t_data *data, int argc, char **argv)
{
	int	i;

	data->number_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->number_eat = ft_atoi(argv[5]);
	else 
		(data->number_eat = -1);
	data->start_time = 0;
	data->philo_threads = NULL;
	data->philos = NULL;
	data->fork_mutexes = NULL;
	data->someone_dead = 0;
	data->someone_full = 0;
	if (pthread_mutex_init(&(data->eating_mutex), NULL) != 0)
		return (1);
	if (pthread_mutex_init(&(data->print_mutex), NULL) != 0)
		return (1);
	data->fork_mutexes = malloc(sizeof(pthread_mutex_t) * data->number_philos);
	if (data->fork_mutexes == NULL)
	{
		ft_free(data);
		return (1);
	}
	i = 0;
	while (i < data->number_philos)
	{
		if (pthread_mutex_init(&((data->fork_mutexes)[i]), NULL) != 0)
			return (1);
		i++;
	}
	data->philos = malloc(sizeof(t_philo) * data->number_philos);
	if (data->philos == NULL)
	{
		ft_free(data);
		return (1);
	}
	data->philo_threads = malloc(sizeof(pthread_t) * data->number_philos);
	if (data->philo_threads == NULL)
	{
		ft_free(data);
		return (1);
	}
	return (0);
}
