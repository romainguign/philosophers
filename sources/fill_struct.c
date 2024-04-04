/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:37:55 by roguigna          #+#    #+#             */
/*   Updated: 2024/04/04 19:13:29 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	get_current_time(void)
{
	struct timeval			tv;
	size_t					time;
	
	if (gettimeofday(&tv, NULL) == -1)
	{
		ft_putstr_fd(TIME_ERROR, 2);
		return (0);
	}
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

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
	size_t i;
	
	i = 0;
	while (i < ft_ato_size_t(argv[1]))
	{
		table->philos[i].id = i + 1;
		table->philos[i].dead = &table->dead;
		table->philos[i].start_time = table->philos[0].start_time;
		table->philos[i].num_of_philos = ft_ato_size_t(argv[1]);
		table->philos[i].time_to_die = ft_ato_size_t(argv[2]);
		table->philos[i].time_to_eat = ft_ato_size_t(argv[3]);
		table->philos[i].time_to_sleep = ft_ato_size_t(argv[4]);
		table->philos[i].last_meal = table->philos->start_time;
		if (argc == 6)
			table->philos[i].meals_required = (int )ft_ato_size_t(argv[5]);
		else
			table->philos[i].meals_required = -1;
		i++;
	}
	if (!check_nums(table, argc))
	{
		ft_putstr_fd(INVALID_ARGUMENT, 2);
		return (0);
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
	table->philos = ft_calloc(ft_ato_size_t(argv[1]) + 1, sizeof(t_philo));
	if (!table->philos)
	{
		ft_putstr_fd(MALLOC_ERROR, 2);
		free(table);
		return (0);
	}
	table->philos[0].start_time = get_current_time();
	if (!table->philos[0].start_time || !fill_infos(argv, argc, table))
	{
		free_all(table);
		return (0);
	}
	return (table);
}
