/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:58:10 by roguigna          #+#    #+#             */
/*   Updated: 2024/04/12 10:10:10 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

# define MALLOC_ERROR		"philosophers: malloc: failed allocation memory\n"
# define TIME_ERROR			"philosophers: gettimeofday: failed\n"
# define INVALID_ARGUMENT	"philosophers: an argument is not valid\n"
# define JOIN_ERROR			"philosophers: pthread_join: failed joining \
thread\n"
# define THREAD_ERROR		"philosophers: pthread_create: failed creating \
thread\n"

# define EATING_MESSAGE		"%lld %d is eating\n"
# define FORK_MESSAGE		"%lld %d has taken a fork\n"
# define SLEEPING_MESSAGE	"%lld %d is sleeping\n"
# define THINKING_MESSAGE	"%lld %d is thinking\n"
# define DEAD_MESSAGE		"%lld %d died\n"

typedef struct s_philo
{
	int				id;
	int				*dead;
	int				num_of_philos;
	int				meals_required;
	int				meals_eaten;
	int				is_eating;
	long long int	last_meal;
	long long int	time_to_die;
	long long int	time_to_eat;
	long long int	time_to_sleep;
	long long int	start_time;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}	t_philo;

typedef struct s_table
{
	t_philo			*philos;
	int				dead;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
}	t_table;

//utils:
long long int	get_current_time(void);
void			ft_putstr_fd(char *s, int fd);
void			*ft_calloc(size_t nmemb, size_t size);
int				ft_strlen(char *str);
int				ft_isdigit(int c);
void    		ft_sleep(size_t    overclock);
void			state_message(t_philo *philo, char *message);

//parsing:
int				check_argv(char **argv, int argc);
t_table			*fill_struct(char **argv, int argc);
long long int	ft_atoll(const char *nptr);

//routine:
void			*ft_routine(void *data);
int				is_finish(t_philo *philo);

//monitoring
void			philo_monitoring(t_table *table);

//free
void			free_all(t_table *table);

#endif