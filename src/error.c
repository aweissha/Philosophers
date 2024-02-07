/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:04:37 by aweissha          #+#    #+#             */
/*   Updated: 2024/02/07 12:39:10 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_error(char *message, int code)
{
	perror(message);
	exit(code);
}

void	ft_free(t_data *data)
{
	int	i;

	i = 0;
	if (data->philos != NULL)
		free(data->philos);
	if (data->forks != NULL)
		free(data->forks);
	if (data->mutex_print != NULL)
	{
		pthread_mutex_destroy(data->mutex_print);
		free(data->mutex_print);
	}
	if (data->fork_mutexes != NULL)
	{
		while (i < data->number_philos)
		{
			pthread_mutex_destroy(&(data->fork_mutexes[i]));
			i++;
		}
		free(data->fork_mutexes);
	}
	free(data);
}

void	ft_free_error(char *message, int code, t_data *data)
{
	ft_free(data);
	ft_error(message, code);
}

void	ft_join_and_free(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_philos)
	{
		if (pthread_join(((data->philos)[i]).philo, NULL) != 0)
			ft_free_error("error joining of thread\n", EXIT_FAILURE, data);
		i++;
	}
	ft_free(data);
}
