/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:27:08 by aweissha          #+#    #+#             */
/*   Updated: 2024/02/02 12:54:02 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{


	printf("time in ms: %ld\n", time_ms());
	
	// struct timeval	time;
	// long	daytime_seconds;
	
	// gettimeofday(&time, NULL);
	// printf("seconds: %ld\n", time.tv_sec);
	// printf("useconds: %d\n", time.tv_usec);
	printf("YEARS: %ld\n", time_ms() / 1000 / 60 / 60 / 24 / 365);
	// daytime
	// long	seconds_per_day;
	
	// seconds_per_day = 60 * 60 * 24;
	// daytime_seconds = (time.tv_sec % seconds_per_day);
	// printf(": %d\n", time.tv_usec);



}