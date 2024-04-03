/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:49:15 by roguigna          #+#    #+#             */
/*   Updated: 2024/04/03 15:27:18 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		init_threads(t_table *table)
{
	int	i;
	
	pthread_mutex_init(&table->write_lock, NULL);
	pthread_mutex_init(&table->dead_lock, NULL);
	pthread_mutex_init(&table->meal_lock, NULL);
	i = 0;
	while (table->philos[i].num_of_philos)
	{
		table->philos[i].write_lock = &table->write_lock;
		table->philos[i].dead_lock = &table->write_lock;
		table->philos[i].meal_lock = &table->write_lock;
		i++;
	}
	return (1);
}

t_table	*init_philo(char **argv, int argc)
{
	t_table *table;

	if (!check_argv(argv, argc))
		return (0);
	table = fill_struct(argv, argc);
	if (!table)
		return (0);
	if (!init_threads(table))
		return (0);
	return (table);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	if (argc < 5 || argc > 6)
	{
		write(2, "Invalid number of arguments\n", 28);
		return (1);
	}
	table = init_philo(argv, argc);
	if (!table)
		return (1);
	free_all(table);
	return (0);
}