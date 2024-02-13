/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:27:08 by aweissha          #+#    #+#             */
/*   Updated: 2024/02/13 16:02:43 by aweissha         ###   ########.fr       */
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
	if (init_data(&data, argc, argv) == 1)
		return (1);
	create_threads(&data);
	ft_join_and_free(&data);
}

// Todo:
// check for memory leaks
// Norminette
