/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:49:15 by roguigna          #+#    #+#             */
/*   Updated: 2024/04/12 10:40:07 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	exec_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philos->num_of_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL, ft_routine,
				&table->philos[i]))
		{
			ft_putstr_fd(THREAD_ERROR, 2);
			return (0);
		}
		i++;
	}
	philo_monitoring(table);
	i = 0;
	while (i < table->philos->num_of_philos)
	{
		if (pthread_join(table->philos[i].thread, NULL))
		{
			ft_putstr_fd(JOIN_ERROR, 2);
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_threads(t_table *table)
{
	int	i;

	pthread_mutex_init(&table->write_lock, NULL);
	pthread_mutex_init(&table->dead_lock, NULL);
	pthread_mutex_init(&table->meal_lock, NULL);
	i = 0;
	while (table->philos[i].num_of_philos)
	{
		table->philos[i].l_fork = ft_calloc(1, sizeof(pthread_mutex_t));
		if (!table->philos[i].l_fork)
		{
			ft_putstr_fd(MALLOC_ERROR, 2);
			return (0);
		}
		pthread_mutex_init(table->philos[i].l_fork, NULL);
		// if (i + 1 < table->philos[i].num_of_philos)
		// 	table->philos[i + 1].r_fork = table->philos[i].l_fork;
		table->philos[i].write_lock = &table->write_lock;
		table->philos[i].dead_lock = &table->dead_lock;
		table->philos[i].meal_lock = &table->meal_lock;
		i++;
	}
	// if (table->philos[i].num_of_philos != 1)
	// 	table->philos[0].r_fork = table->philos[i - 1].l_fork;
	return (1);
}

t_table	*init_philo(char **argv, int argc)
{
	t_table	*table;

	if (!check_argv(argv, argc))
		return (0);
	table = fill_struct(argv, argc);
	if (!table)
		return (0);
	if (!init_threads(table))
	{
		free_all(table);
		return (0);
	}
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
	if (!exec_threads(table))
	{
		free_all(table);
		return (1);
	}
	free_all(table);
	return (0);
}
