/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:25:00 by aweissha          #+#    #+#             */
/*   Updated: 2024/02/10 15:10:55 by aweissha         ###   ########.fr       */
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

typedef struct s_data t_data;

typedef struct s_philo
{
	int				philo_index;
	int				philo_number;
	pthread_mutex_t	*right_fork_mutex;
	pthread_mutex_t	*left_fork_mutex;
	int				number_eaten;
	long			last_meal_time;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				number_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				number_eat;
	long			start_time;
	pthread_t		*philo_threads;
	t_philo			*philos;
	pthread_mutex_t	*fork_mutexes;
	pthread_mutex_t	eating_mutex;
	pthread_t		termination_checker;
	int				someone_dead;
	int				someone_full;
}	t_data;

void	ft_error(char *message, int code);
void	ft_free(t_data *data);
void	ft_free_error(char *message, int code, t_data *data);
void	ft_join_and_free(t_data *data);
long	ft_time_ms(void);
int		ft_eat(t_data *data, t_philo *philo);
int		take_forks_up(t_data *data, t_philo *philo);
void	put_forks_down(t_philo *philo);
int		ft_think(t_data *data, t_philo *philo);
int		ft_sleep(t_data *data, t_philo *philo);
void	ft_sleep_ms(long duration);
void	*ft_philo(void *arg);
void	ft_create_threads(t_data *data);
t_data	*ft_init_data(int argc, char **argv);

#endif