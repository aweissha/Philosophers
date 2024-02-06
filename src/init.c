/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:43:18 by aweissha          #+#    #+#             */
/*   Updated: 2024/02/06 17:39:57 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_create_philos(t_data *data)
{
	int	i;
	t_philo philo;

	data->philos = malloc(sizeof(t_philo) * data->number_philos);
	if (data->philos == NULL)
		ft_free_error("memory allocation for philos failed\n", EXIT_FAILURE, data);
	i = 0;
	while (i < data->number_philos)
	{
		philo = data->philos[i];
		philo.philo_index = i;
		philo.philo_number = i + 1;
		philo.number_eaten = 0;
		philo.last_meal_time = 0;
		philo.data = data;
		philo.right_fork_mutex = &(data->fork_mutexes[i]);
		philo.right_fork = &(data->forks[i]);
		if (i > 0)
		{
			philo.left_fork_mutex = &(data->fork_mutexes[i - 1]);
			philo.left_fork = &(data->forks[i - 1]);
		}
		else
		{
			philo.left_fork_mutex = &(data->fork_mutexes[data->number_philos - 1]);
			philo.left_fork = &(data->forks[data->number_philos - 1]);
		}
		if (pthread_create(&(philo.philo), NULL, ft_philo, &philo) != 0)
			ft_free_error("creation of thread failed\n", EXIT_FAILURE, data);
		i++;
	}
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
	data->philos = NULL;
	data->forks = NULL;
	data->mutex_print = NULL;
	data->mutex_print = malloc(sizeof(pthread_mutex_t));
	if (data->mutex_print == NULL)
		ft_free_error("memory allocation for mutex_print failed", EXIT_FAILURE, data);
	if (pthread_mutex_init(data->mutex_print, NULL) != 0)
		ft_free_error("mutex_print initialization failed\n", EXIT_FAILURE, data);
	data->fork_mutexes = NULL;
	data->fork_mutexes = malloc(sizeof(pthread_mutex_t) * data->number_philos);
	if (data->fork_mutexes == NULL)
		ft_free_error("memory allocation for fork_mutexes failed", EXIT_FAILURE, data);
	i = 0;
	while (i < data->number_philos)
	{
		if (pthread_mutex_init(&(data->fork_mutexes[i]), NULL) != 0)
			ft_free_error("fork_mutex initialization failed\n", EXIT_FAILURE, data);
		i++;
	}
	data->forks = malloc(sizeof(int) * data->number_philos);
	if (data->forks == NULL)
		ft_free_error("memory allocation for forks array failed", EXIT_FAILURE, data);
	i = 0;
	while (i < data->number_philos)
	{
		data->forks[i] = 1;
		i++;
	}
	data->start_time = ft_time_ms();
	return (data);
}
