/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:25:00 by aweissha          #+#    #+#             */
/*   Updated: 2024/02/04 15:50:44 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_philo
{
	pthread_t		philo;
	int				philo_index;
	int				philo_number;
	int				right_fork;
	int				number_eaten;
	long			last_meal_time;
	pthread_mutex_t	*mutex_fork;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				argc;
	char			**argv;
	int				number_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				number_eat;
	long			start_time;
	t_philo			*philos;
	pthread_mutex_t	*mutex_print;
}	t_data;



void	ft_error(char *message, int code);
void	ft_free(t_data *data);
void	ft_free_error(char *message, int code, t_data *data);
long	time_ms(void);


#endif