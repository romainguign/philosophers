#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define MALLOC_ERROR "philosophers: malloc: failed allocation memory\n"
# define TIME_ERROR "philosophers: gettimeofday: failed\n"
# define INVALID_ARGUMENT "philosophers: an argument is not valid\n"

# define GRAY "\033[0;90m"
# define RED "\033[0;91m"
# define GREEN "\033[3;92m"
# define YELLOW "\033[0;93m"
# define BLUE "\033[3;94m"
# define MAGENTA "\033[0;95m"
# define CYAN "\033[0;96m"
# define WHITE "\033[0;97m"

# define EATING_MESSAGE "\e[0;92m%zu %d is eating\n\e[m"
# define FORK_MESSAGE "\e[0;93m%zu %d has taken a fork\n\e[m"
# define SLEEPING_MESSAGE "\e[0;95m%zu %d is sleeping\n\e[m"
# define THINKING_MESSAGE "\e[0;94m%zu %d is thinking\n\e[m"
# define DEAD_MESSAGE "\e[0;91m%zu %d died\n\e[m"

typedef struct s_philo
{
	int				id;
	int				*dead;
	int				num_of_philos;
	int				meals_required;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
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
size_t	get_current_time(void);
void	ft_putstr_fd(char *s, int fd);
void	*ft_calloc(size_t nmemb, size_t size);
int     ft_strlen(char *str);
int     ft_isdigit(int c);

//parsing:
int check_argv(char **argv, int argc);
t_table *fill_struct(char **argv, int argc);
size_t	ft_ato_size_t(const char *nptr);

//routine:
void *ft_routine(void *data);
int	is_finish(t_philo *philo);

//message:
void	state_message(t_philo *philo, char *message);

//free
void    free_all(t_table *table);

#endif