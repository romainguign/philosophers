/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:27:01 by roguigna          #+#    #+#             */
/*   Updated: 2024/04/04 17:30:19 by roguigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_ato_size_t(const char *nptr)
{
	size_t	i;
	size_t	nbr;
	size_t	negative;

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
