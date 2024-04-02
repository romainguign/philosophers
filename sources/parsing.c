/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:27:01 by roguigna          #+#    #+#             */
/*   Updated: 2024/04/02 18:21:02 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long int	ft_atoll(const char *nptr)
{
	long long int	i;
	long long int	nbr;
	long long int	negative;

	i = 0;
	nbr = 0;
	negative = 0;
	while ((nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13)))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			negative = 1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nbr = nbr * 10 + (nptr[i] - 48);
		i++;
	}
	if (negative == 1)
		nbr *= -1;
	return (nbr);
}

int	check_arg(char *args)
{
	int	j;

	j = 0;
	if (!ft_isdigit(args[j]) && (args[j] != '+' && args[j] != '-'))
		return (0);
	if ((args[j] == '+' || args[j] == '-') && !ft_isdigit(args[j + 1]))
		return (0);
	j++;
	while (args[j])
	{
		if (!ft_isdigit(args[j]))
			return (0);
		j++;
	}
	return (1);
}

int check_nums(t_philo *philo, int argc)
{
    if (philo->num_of_philos < 0 || philo->time_to_die < 0
        || philo->time_to_eat < 0 || philo->time_to_sleep < 0)
        return (0);
    if (argc == 6 && philo->last_meal < 0)
        return (0);
    return (1);
}

t_philo *fill_struct(char **argv, int argc)
{
    t_philo *philo;
    int i;

    i = 1;
    philo = malloc(1 * sizeof(t_philo));
    if (!philo)
    {
        ft_putstr_fd(MALLOC_ERROR, 2);
        return (0);
    }
    philo->num_of_philos = ft_atoll(argv[1]);
    philo->time_to_die = ft_atoll(argv[2]);
    philo->time_to_eat = ft_atoll(argv[3]);
    philo->time_to_sleep = ft_atoll(argv[4]);
    if (argc == 6)
        philo->last_meal = ft_atoll(argv[5]);
    else
        philo->last_meal = -1;
    if (!check_nums(philo, argc))
    {
        free (philo);
        return (0);
    }
    return (philo);
}

int check_argv(char **argv, int argc)
{
    int i;

    i = 1;
    while (i < argc)
    {
        if (!check_arg(argv[i]))
        {
            ft_putstr_fd(INVALID_ARGUMENT, 2);
            return (0);
        }
        i++;
    }
    return (1);
}
