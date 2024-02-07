/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:27:08 by aweissha          #+#    #+#             */
/*   Updated: 2024/02/07 14:08:54 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;


	data = ft_init_data(argc, argv);
	ft_create_threads(data);

	// sleep(10);

	
	ft_join_and_free(data);
}

// Todo:
// implement death checker...thread, that continuously check if a philosopher is supposed to die
// implement argument checks (therefore check the eval sheet)
