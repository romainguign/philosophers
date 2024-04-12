/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:19:01 by roguigna          #+#    #+#             */
/*   Updated: 2024/04/12 13:47:20 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philos[0].num_of_philos)
	{
		if (table->philos[i].l_fork)
		{
			pthread_mutex_destroy(table->philos[i].l_fork);
			free(table->philos[i].l_fork);
		}
		i++;
	}
	pthread_mutex_destroy(&table->dead_lock);
	pthread_mutex_destroy(&table->meal_lock);
	pthread_mutex_destroy(&table->write_lock);
	free(table->philos);
}

void	free_all(t_table *table)
{
	if (table->philos)
		free_philos(table);
	if (table)
		free(table);
}
