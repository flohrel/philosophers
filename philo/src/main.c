/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:01:42 by flohrel           #+#    #+#             */
/*   Updated: 2021/10/14 06:55:22 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	vars_init(t_vars *vars, t_param *param)
{
	struct timeval	tv;

	param->nb_philo = -1;
	param->time_to_die = -1;
	param->time_to_eat = -1;
	param->time_to_sleep = -1;
	param->nb_eat = -1;
	vars->table = NULL;
	gettimeofday(&tv, NULL);
	vars->start_time = tv.tv_usec;
}

t_philo	*get_last(t_philo *philo)
{
	while (philo->next != NULL)
		philo = philo->next;
	return (philo);
}

int	philo_init(uint32_t nb_philo, t_philo **table)
{
	uint32_t	i;
	t_philo		*philo;
	t_philo		*last;

	i = nb_philo + 1;
	while (--i)
	{
		philo = malloc(sizeof(t_philo));
		if (!philo)
			return (-1);
		philo->id = i;
		philo->last_meal = -1;
		philo->next = *table;
		*table = philo;
	}
	last = get_last(*table);
	last->next = *table;
	return (0);
}

void	free_philo(t_philo *philo, uint32_t nb_philo)
{
	uint32_t	i;
	t_philo		*next;

	i = -1;
	while (++i < nb_philo)
	{
		next = philo->next;
		free(philo);
		philo = next;
	}
}

int	clean_exit(int ret_value, t_vars *vars)
{
	free_philo(vars->table, vars->param.nb_philo);
	return (ret_value);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	vars_init(&vars, &vars.param);
	if (parser(argc, argv, &vars.param) == -1)
		return (EXIT_FAILURE);// initialize every philosopher and put them around the table (circular chained list)
	if (philo_init(vars.param.nb_philo, &vars.table) == -1)
		return (clean_exit(EXIT_FAILURE, &vars));
//	launch();	// create threads, detach them
//	observe();	// create observer thread (waiting for dead philo OR nb_meal == 0) / pthread_join
	return (clean_exit(EXIT_SUCCESS, &vars));
}
