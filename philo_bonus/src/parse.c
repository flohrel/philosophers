/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 17:21:07 by flohrel           #+#    #+#             */
/*   Updated: 2021/11/02 11:40:20 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(int c)
{
	return ((c == ' ') || !((c > 13) || (c < 9)));
}

static int	ft_isdigit(int c)
{
	return (!((c > '9') || (c < '0')));
}

static int	check_overflow(unsigned int nb, int nptr)
{
	unsigned int	n;

	n = (INT_MAX - nptr + '0') / 10;
	if (nb > n)
		return (-1);
	return (0);
}

static int	ft_atoi(const char *nptr)
{
	int	nb;

	while (ft_isspace(*nptr))
		nptr++;
	nb = 0;
	while (*nptr)
	{
		if ((!ft_isdigit(*nptr))
			|| (check_overflow(nb, *nptr) == -1))
			return (0);
		nb = (nb * 10) + (*nptr - '0');
		nptr++;
	}
	return (nb);
}

void	parser(int argc, char **argv, t_param *param)
{
	if ((argc < 5) || (argc > 6))
		exit(EXIT_FAILURE);
	param->nb_philo = ft_atoi(argv[1]);
	param->time_to_die = ft_atoi(argv[2]);
	param->time_to_eat = ft_atoi(argv[3]);
	param->time_to_sleep = ft_atoi(argv[4]);
	if ((param->nb_philo < 1) || (param->nb_philo > PROCESS_MAX)
		|| (param->time_to_die < 0)
		|| (param->time_to_eat < 1)
		|| (param->time_to_sleep < 0))
		exit(EXIT_FAILURE);
	if (argc == 6)
	{
		param->nb_meal = ft_atoi(argv[5]);
		if (param->nb_meal < 1)
			exit(EXIT_FAILURE);
	}
}
