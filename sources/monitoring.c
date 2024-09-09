/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:03:42 by roguigna          #+#    #+#             */
/*   Updated: 2024/04/16 14:23:39 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_if_all_eat(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->meal_lock);
	if (table->philos[0].meals_required == -1)
	{
		pthread_mutex_unlock(&table->meal_lock);
		return (1);
	}
	while (i < table->philos[0].num_of_philos)
	{
		if (table->philos[i].meals_eaten < table->philos[0].meals_required)
		{
			pthread_mutex_unlock(&table->meal_lock);
			return (1);
		}
		i++;
	}
	pthread_mutex_unlock(&table->meal_lock);
	pthread_mutex_lock(&table->dead_lock);
	table->dead = 1;
	pthread_mutex_unlock(&table->dead_lock);
	return (0);
}

int	check_if_someone_died(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philos[0].num_of_philos)
	{
		pthread_mutex_lock(&table->meal_lock);
		if (get_current_time() - table->philos[i].last_meal
			> table->philos[i].time_to_die)
		{
			pthread_mutex_lock(&table->dead_lock);
			table->dead = 1;
			pthread_mutex_unlock(&table->dead_lock);
			pthread_mutex_lock(&table->write_lock);
			printf(DEAD_MESSAGE, get_current_time()
				- table->philos[0].start_time, table->philos[i].id);
			pthread_mutex_unlock(&table->write_lock);
			pthread_mutex_unlock(&table->meal_lock);
			return (0);
		}
		pthread_mutex_unlock(&table->meal_lock);
		i++;
	}
	return (1);
}

void	philo_monitoring(t_table *table)
{
	while (1)
	{
		if (!check_if_all_eat(table) || !check_if_someone_died(table))
			break ;
		usleep(10);
	}
	return ;
}
