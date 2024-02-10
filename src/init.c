/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:43:18 by aweissha          #+#    #+#             */
/*   Updated: 2024/02/10 14:02:10 by aweissha         ###   ########.fr       */
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
				printf("Philosopher %d died of starvation\n", ((data->philos)[i]).philo_number);
				pthread_mutex_unlock(&(data->eating_mutex));	
				return (NULL);
			}
			if (data->number_eat >= 0)
			{
				number_eaten = ((data->philos)[i]).number_eaten;
				if (number_eaten >= data->number_eat)
				{
					data->someone_full = 1;
					printf("Philosopher %d has eaten enough\n", ((data->philos)[i]).philo_number);
					pthread_mutex_unlock(&(data->eating_mutex));
					return (NULL);
				}
			}
			i++;
		}
		pthread_mutex_unlock(&(data->eating_mutex));
		usleep(100);
	}
	return (arg);
}

void	ft_create_threads(t_data *data)
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
			ft_free_error("creation of thread failed\n", EXIT_FAILURE, data);
		i++;
	}
	if (pthread_create(&(data->termination_checker), NULL, &ft_termination_checker, data) != 0)
		ft_free_error("creation of thread failed\n", EXIT_FAILURE, data);
}

t_data	*ft_init_data(int argc, char **argv)
{
	t_data			*data;
	int				i;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		ft_error("memory allocation for data struct failed\n", EXIT_FAILURE);
	data->number_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->number_eat = ft_atoi(argv[5]);
	else 
		(data->number_eat = -1);
	data->start_time = 0;
	data->philos = NULL;
	data->fork_mutexes = NULL;
	data->someone_dead = 0;
	data->someone_full = 0;
	if (pthread_mutex_init(&(data->eating_mutex), NULL) != 0)
		ft_free_error("eating_mutex initialization failed\n", EXIT_FAILURE, data);
	data->fork_mutexes = malloc(sizeof(pthread_mutex_t) * data->number_philos);
	if (data->fork_mutexes == NULL)
		ft_free_error("memory allocation for fork_mutexes failed", EXIT_FAILURE, data);
	i = 0;
	while (i < data->number_philos)
	{
		if (pthread_mutex_init(&((data->fork_mutexes)[i]), NULL) != 0)
			ft_free_error("fork_mutex initialization failed\n", EXIT_FAILURE, data);
		i++;
	}
	data->philos = malloc(sizeof(t_philo) * data->number_philos);
	if (data->philos == NULL)
		ft_free_error("memory allocation for philos failed\n", EXIT_FAILURE, data);
	data->philo_threads = malloc(sizeof(pthread_t) * data->number_philos);
	if (data->philo_threads == NULL)
		ft_free_error("memory allocation for philo_threads failed\n", EXIT_FAILURE, data);
	return (data);
}
