/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:25:00 by aweissha          #+#    #+#             */
/*   Updated: 2024/02/13 16:14:27 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include "../libft/libft.h"

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				philo_index;
	int				philo_number;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	int				number_eaten;
	long			last_meal_time;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				nb_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				number_eat;
	long			start_time;
	pthread_t		*philo_threads;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	eating_mutex;
	pthread_mutex_t	print_mutex;
	pthread_t		termination_checker;
	int				someone_dead;
	pthread_mutex_t	termination_mutex;
	int				all_full;
}	t_data;

// input.c: validation of input
int		validate_input(int argc, char **argv);
int		check_range(int argc, char **argv);
int		only_digits(int argc, char **argv);

// error.c: memory and error handling
void	ft_free(t_data *data);
int		ft_join_and_free(t_data *data);

// utils.c: utils
long	ft_time_ms(void);

// philosophers actions
int		ft_eat(t_data *data, t_philo *philo);
int		take_forks_up(t_data *data, t_philo *philo);
void	put_forks_down(t_philo *philo);
int		ft_think(t_data *data, t_philo *philo);
int		ft_sleep(t_data *data, t_philo *philo);
void	ft_sleep_ms(long duration);
void	*ft_philo(void *arg);

// init.c: initialization of data struct
int		init_data(t_data *data, int argc, char **argv);
void	init_vars(t_data *data, int argc, char **argv);
int		data_malloc(t_data *data);
int		init_mutexes(t_data *data);

// threads.c: threads creation
int		create_threads(t_data *data);
void	init_philos(t_data *data);

//  termination.c: termination checker thread
void	*termination_checker(void *arg);
int		check_death(t_data *data);
int		check_all_full(t_data *data);
int		dead_or_full(t_data *data);

#endif