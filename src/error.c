/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:04:37 by aweissha          #+#    #+#             */
/*   Updated: 2024/02/04 14:46:16 by aweissha         ###   ########.fr       */
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
	{
		while (i < data->number_philos)
		{
			if (data->philos[i].mutex_fork != NULL)
				pthread_mutex_destroy(data->philos[i].mutex_fork);
			i++;
		}
		free(data->philos);		
	}
	if (data->mutex_print != NULL)
		pthread_mutex_destroy(data->mutex_print);
	free(data);
}

void	ft_free_error(char *message, int code, t_data *data)
{
	ft_free(data);
	ft_error(message, code);
}
