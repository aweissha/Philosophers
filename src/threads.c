/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 09:58:34 by aweissha          #+#    #+#             */
/*   Updated: 2024/02/13 16:19:21 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		data->philos[i].philo_index = i;
		data->philos[i].philo_number = i + 1;
		data->philos[i].right_fork = &((data->forks)[i]);
		data->philos[i].number_eaten = 0;
		data->philos[i].data = data;
		if (i > 0)
			data->philos[i].left_fork = &((data->forks)[i - 1]);
		else
			data->philos[i].left_fork = &((data->forks)[(data->nb_philos) - 1]);
		i++;
	}
}

int	create_threads(t_data *data)
{
	int	i;

	init_philos(data);
	data->start_time = ft_time_ms();
	i = 0;
	while (i < data->nb_philos)
	{
		((data->philos)[i]).last_meal_time = ft_time_ms();
		if (pthread_create(&((data->philo_threads)[i]), NULL,
			&ft_philo, &((data->philos)[i])) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&(data->termination_checker), NULL,
			&termination_checker, data) != 0)
		return (1);
	return (0);
}
