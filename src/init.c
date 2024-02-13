/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:43:18 by aweissha          #+#    #+#             */
/*   Updated: 2024/02/13 16:15:21 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_vars(t_data *data, int argc, char **argv)
{
	data->nb_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->number_eat = ft_atoi(argv[5]);
	else
		data->number_eat = -1;
	data->start_time = 0;
	data->philo_threads = NULL;
	data->philos = NULL;
	data->forks = NULL;
	data->someone_dead = 0;
	data->all_full = 0;
}

int	data_malloc(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (data->forks == NULL)
	{
		ft_free(data);
		return (1);
	}
	data->philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (data->philos == NULL)
	{
		ft_free(data);
		return (1);
	}
	data->philo_threads = malloc(sizeof(pthread_t) * data->nb_philos);
	if (data->philo_threads == NULL)
	{
		ft_free(data);
		return (1);
	}
	return (0);
}

int	init_mutexes(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&(data->eating_mutex), NULL) != 0)
		return (1);
	if (pthread_mutex_init(&(data->print_mutex), NULL) != 0)
		return (1);
	if (pthread_mutex_init(&(data->termination_mutex), NULL) != 0)
		return (1);
	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_mutex_init(&((data->forks)[i]), NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	init_vars(data, argc, argv);
	if (data_malloc(data) == 1)
		return (1);
	if (init_mutexes(data) == 1)
		return (1);
	return (0);
}
