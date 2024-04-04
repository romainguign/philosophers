/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:35:30 by roguigna          #+#    #+#             */
/*   Updated: 2024/04/04 19:46:46 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	state_message(t_philo *philo, char *message)
{
	size_t  time;

	if (!is_finish(philo))
		return ;
	time = get_current_time() - philo->start_time;
	pthread_mutex_lock(philo->write_lock);
	printf(message, time, philo->id);
	pthread_mutex_unlock(philo->write_lock);
}