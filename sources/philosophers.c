/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:49:15 by roguigna          #+#    #+#             */
/*   Updated: 2024/04/02 18:21:50 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*init_philo(char **argv, int argc)
{
	t_philo *philo;

	if (!check_argv(argv, argc))
		return (0);
	philo = fill_struct(argv, argc);
	if (!philo)
	{
		ft_putstr_fd(INVALID_ARGUMENT, 2);
		return (0);
	}
	return (philo);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;

	if (argc < 5 || argc > 6)
	{
		write(2, "Invalid number of arguments\n", 28);
		return (1);
	}
	philo = init_philo(argv, argc);
	if (!philo)
		return (1);
	free(philo);
	return (0);
}