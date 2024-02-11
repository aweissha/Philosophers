/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:27:08 by aweissha          #+#    #+#             */
/*   Updated: 2024/02/11 17:59:44 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (validate_input(argc, argv) == 1)
	{
		printf("Error: Input is not valid\n");
		return (1);	
	}
	if (ft_init_data(&data, argc, argv) == 1)
		return (1);
	ft_create_threads(&data);
	ft_join_and_free(&data);
}

// Todo:
//  clean up code
//  handle case of only 1 philo
// check for memory leaks
// Norminette
