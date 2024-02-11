/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 10:59:28 by aweissha          #+#    #+#             */
/*   Updated: 2024/02/11 11:57:57 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_range(int argc, char **argv)
{
	int	i;

	if (!((ft_atoi(argv[1]) >= 1) && (ft_atoi(argv[1]) <= 200)))
		return (1);
	if (argc == 6 && (ft_atoi(argv[5]) <= 0))
		return (1);
	i = 2;
	while (i < 5)
	{
		if (ft_atoi(argv[i]) < 60)
			return (1);
		i++;
	}
	return (0);
}

int	only_digits(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (ft_isdigit(argv[i][j]) == 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	validate_input(int argc, char **argv)
{
	if (!(argc >= 5 && argc <= 6))
		return (1);
	if (only_digits(argc, argv) == 1)
		return (1);
	if (check_range(argc, argv) == 1)
		return (1);
	return (0);
}
