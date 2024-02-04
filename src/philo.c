/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:27:08 by aweissha          #+#    #+#             */
/*   Updated: 2024/02/04 15:23:32 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_create_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->number_philos);
	if (data->philos == NULL)
		ft_free_error("memory allocation for philos failed\n", EXIT_FAILURE, data);
	i = 0;
	while (i < data->number_philos)
	{
		data->philos[i].philo_number = i;
		data->philos[i].philo_number = i + 1;
		data->philos[i].number_eaten = 0;
		data->philos[i].right_fork = 1;
		data->philos[i].last_meal_time = 0;
		data->philos[i].data = data;
		data->philos[i].mutex_fork = NULL;
		if (pthread_mutex_init(data->philos[i].mutex_fork, NULL) != 0)
			ft_free_error("mutex_fork initialization failed\n", EXIT_FAILURE, data);
		if (pthread_create(&(data->philos[i].philo), NULL, ft_philo, &(data->philos[i])) != 0)
			ft_free_error("creation of thread failed\n", EXIT_FAILURE, data);
		i++;
	}
}

t_data	*ft_init_data(int argc, char **argv)
{
	t_data	*data;
	
	data = malloc(sizeof(t_data));
	if (data == NULL)
		ft_error("memory allocation for data struct failed\n", EXIT_FAILURE);
	data->argc = argc;
	data->argv = argv;
	data->number_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->number_eat = ft_atoi(argv[5]);
	data->philos = NULL;
	data->mutex_print = NULL;
	if (pthread_mutex_init(data->mutex_print, NULL) != 0)
		ft_free_error("mutex_print initialization failed\n", EXIT_FAILURE, data);
	data->start_time = ft_time_ms();
}

void	ft_join_and_free(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_philos)
	{
		if (pthread_join(&(data->philos[i].philo), NULL) != 0)
			ft_free_error("error joining of thread\n", EXIT_FAILURE, data);
		i++;
	}
	ft_free(data);
}

void	ft_eat(t_data *data, t_philo *philo)
{
	if (philo->philo_number > 1)
	{
		while (1)
		{
			if ((philo->right_fork == 1 && data->philos[philo->philo_index - 1].right_fork == 1))
				use_fork(data, philo);
			break ;
		}
	}
	else if (philo->philo_number == 1)
	{
		while (1)
		{
			if (philo->right_fork == 1 && data->philos[(data->number_philos - 1)].right_fork == 1)
				use_fork(data, philo);
			break ;
		}
	}
}

void	use_fork(t_data *data, t_philo *philo)
{
	long	timestamp;

	take_forks_up(data, philo);
	timestamp = ft_time_ms() - data->start_time;	
	printf("%ld %d is eating\n", timestamp, philo->philo_number);	
	usleep((data->time_to_eat) * 1000);
	put_forks_down(data, philo);
}

void	take_forks_up(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_fork);
	philo->right_fork--;
	if (philo->philo_number == 1)
	{
		pthread_mutex_lock(data->philos[data->number_philos - 1].mutex_fork);
		data->philos[data->number_philos - 1].right_fork--;		
	}
	else
	{
		pthread_mutex_lock(data->philos[philo->philo_index - 1].mutex_fork);
		data->philos[philo->philo_index - 1].right_fork--;
	}
}

void	put_forks_down(t_data *data, t_philo *philo)
{
	philo->right_fork++;
	if (philo->philo_number == 1)
	{
		data->philos[data->number_philos - 1].right_fork++;		
		pthread_mutex_unlock(data->philos[data->number_philos - 1].mutex_fork);
	}
	else
	{
		data->philos[philo->philo_index - 1].right_fork++;
		pthread_mutex_unlock(data->philos[philo->philo_index - 1].mutex_fork);
	}
	pthread_mutex_unlock(philo->mutex_fork);
}

void	ft_think(t_data *data, t_philo *philo)
{
	long	timestamp;

	timestamp = ft_time_ms() - data->start_time;
	printf("%ld %d is thinking\n", timestamp, philo->philo_number);
}

void	ft_sleep(t_data *data, t_philo *philo)
{
	long	timestamp;

	timestamp = ft_time_ms() - data->start_time;
	printf("%ld %d is sleeping\n", timestamp, philo->philo_number);
	usleep((data->time_to_sleep) * 1000);
}

void	*ft_philo(void *arg)
{
	t_philo *philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
		ft_eat(data, philo);
		ft_think(data, philo);
		ft_sleep(data, philo);
	}
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = ft_init_data(argc, argv);
	ft_create_philos(data);


	
	ft_join_and_free(data);


	// printf("time in ms: %ld\n", time_ms());
	
	// struct timeval	time;
	// long	daytime_seconds;
	
	// gettimeofday(&time, NULL);
	// printf("seconds: %ld\n", time.tv_sec);
	// printf("useconds: %d\n", time.tv_usec);
	// printf("YEARS: %ld\n", time_ms() / 1000 / 60 / 60 / 24 / 365);
	// daytime
	// long	seconds_per_day;
	
	// seconds_per_day = 60 * 60 * 24;
	// daytime_seconds = (time.tv_sec % seconds_per_day);
	// printf(": %d\n", time.tv_usec);



}