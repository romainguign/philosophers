#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define MALLOC_ERROR "philosophers: malloc: failed allocation memory\n"
# define INVALID_ARGUMENT "philosophers: an argument is not valid\n"

typedef struct s_philo
{
	int				id;
	int				*dead;
	int				num_of_philos;
	long long int	last_meal;
	long long int	time_to_die;
	long long int	time_to_eat;
	long long int	time_to_sleep;
	long long int	start_time;
	pthread_t		thread;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}   t_philo;

typedef struct s_table
{
	t_philo			*philos;
	int				dead;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
}	t_table;

//utils:
void	ft_putstr_fd(char *s, int fd);
void	*ft_calloc(size_t nmemb, size_t size);
int     ft_strlen(char *str);
int     ft_isdigit(int c);

//parsing:
int check_argv(char **argv, int argc);
t_table *fill_struct(char **argv, int argc);
long long int	ft_atoll(const char *nptr);

//free
void    free_all(t_table *table);

#endif