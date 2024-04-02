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
	long long int	last_meal;
	long long int	time_to_die;
	long long int	time_to_eat;
	long long int	time_to_sleep;
	long long int	start_time;
	int				num_of_philos;
}   t_philo;

//utils:
void	ft_putstr_fd(char *s, int fd);
int     ft_strlen(char *str);
int     ft_isdigit(int c);

//parsing:
int check_argv(char **argv, int argc);
t_philo *fill_struct(char **argv, int argc);
#endif