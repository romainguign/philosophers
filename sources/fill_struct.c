/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:37:55 by roguigna          #+#    #+#             */
/*   Updated: 2024/04/03 14:23:29 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int check_nums(t_table *table, int argc)
{
	if (table->philos->num_of_philos < 1 || table->philos->time_to_die < 1
		|| table->philos->time_to_eat < 1 || table->philos->time_to_sleep < 1)
		return (0);
	if (argc == 6 && table->philos->last_meal < 0)
		return (0);
	return (1);
}

int fill_infos(char **argv, int argc, t_table *table)
{
	int i;
	int nb_of_philos;
	
	i = 0;
	nb_of_philos = ft_atoll(argv[1]);
	while (i < nb_of_philos)
	{
		table->philos[i].num_of_philos = nb_of_philos;
		table->philos[i].time_to_die = ft_atoll(argv[2]);
		table->philos[i].time_to_eat = ft_atoll(argv[3]);
		table->philos[i].time_to_sleep = ft_atoll(argv[4]);
		if (argc == 6)
			table->philos[i].last_meal = ft_atoll(argv[5]);
		else
			table->philos[i].last_meal = -1;
		i++;
	}
	if (!check_nums(table, argc))
	{
		ft_putstr_fd(INVALID_ARGUMENT, 2);
		free_all(table);
		return (0);
	}
	return (1);
}

int fill_philos(t_table *table)
{
	int i;

	i = 0;
	while (table->philos[i].num_of_philos != 0)
	{
		printf("%d, %lld, %lld, %lld, %lld\n", table->philos->num_of_philos, table->philos->time_to_die, table->philos->time_to_eat, table->philos->time_to_sleep, table->philos->last_meal);
		i++;
	}
	return (1);
}

t_table *fill_struct(char **argv, int argc)
{
	t_table *table;
	int i;

	i = 1;
	table = ft_calloc(1, sizeof(t_table));
	if (!table)
	{
		ft_putstr_fd(MALLOC_ERROR, 2);
		return (0);
	}
	table->philos = ft_calloc(ft_atoll(argv[1]) + 1, sizeof(t_philo));
	if (!table->philos)
	{
		ft_putstr_fd(MALLOC_ERROR, 2);
		free(table);
		return (0);
	}
	if (!fill_infos(argv, argc, table))
		return (0);
	if (!fill_philos(table))
		return (0);
	return (table);
}
