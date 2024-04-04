/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:14:58 by roguigna          #+#    #+#             */
/*   Updated: 2024/04/04 19:56:01 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sleeping(t_philo *philo)
{
	if (philo->num_of_philos == 1)
		return ;
	state_message(philo, SLEEPING_MESSAGE);
	usleep(philo->time_to_sleep * 1000);
}

void	eating(t_philo *philo)
{
	// if (philo->num_of_philos == 1)
	// {
	// 	usleep(philo->time_to_die * 1000 + 1000);
	// 	is_finish(philo);
	// 	return ;	
	// }
	pthread_mutex_lock(philo->l_fork);
	state_message(philo, FORK_MESSAGE);
	pthread_mutex_lock(philo->r_fork);
	state_message(philo, FORK_MESSAGE);
	state_message(philo, EATING_MESSAGE);
	usleep(philo->time_to_eat * 1000);
	philo->meals_eaten++;
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

int	is_finish(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (0);
	}
	if (get_current_time() - philo->last_meal > philo->time_to_die)
	{
		*philo->dead = 1;
		pthread_mutex_unlock(philo->dead_lock);
		pthread_mutex_lock(philo->write_lock);
		printf(DEAD_MESSAGE, get_current_time() - philo->start_time, philo->id);
		pthread_mutex_unlock(philo->write_lock);
		return (0);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (1);
}

void	*ft_routine(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (is_finish(philo) == 0)
			return (NULL);
		eating(philo);
		sleeping(philo);
		if (philo->num_of_philos != 1)
			state_message(philo, THINKING_MESSAGE);
		if (philo->meals_eaten == philo->meals_required)
		{
			pthread_mutex_lock(philo->dead_lock);
			*philo->dead = 1;
			pthread_mutex_unlock(philo->dead_lock);
			return (NULL);
		}
	}
	return (NULL);
}
