/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:04:37 by aweissha          #+#    #+#             */
/*   Updated: 2024/02/13 16:32:38 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_free(t_data *data)
{
	int	i;

	i = 0;
	if (data->forks != NULL)
	{
		while (i < data->nb_philos)
		{
			pthread_mutex_destroy(&(data->forks[i]));
			i++;
		}
		free(data->forks);
	}
	if (data->philos != NULL)
		free(data->philos);
	if (data->philo_threads != NULL)
		free(data->philo_threads);
	pthread_mutex_destroy(&(data->eating_mutex));
	pthread_mutex_destroy(&(data->print_mutex));
	pthread_mutex_destroy(&(data->termination_mutex));
}

int	join_and_free(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_join((data->termination_checker), NULL) != 0)
		return (1);
	while (i < data->nb_philos)
	{
		if (pthread_join(((data->philo_threads)[i]), NULL) != 0)
			return (1);
		i++;
	}
	ft_free(data);
	return (0);
}
