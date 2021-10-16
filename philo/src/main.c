/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:01:42 by flohrel           #+#    #+#             */
/*   Updated: 2021/10/16 18:25:07 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	vars_init(t_vars *vars, t_param *param)
{
	struct timeval	tv;

	vars->table = NULL;
	param->nb_philo = -1;
	param->time_to_die = -1;
	param->time_to_eat = -1;
	param->time_to_sleep = -1;
	param->nb_eat = -1;
	gettimeofday(&tv, NULL);
	param->start_time = tv.tv_usec;
	param->has_ended = false;
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
		return (EXIT_FAILURE);
	if (philo_init(vars.param.nb_philo, &vars.table, &vars.param) == -1)
		return (clean_exit(EXIT_FAILURE, &vars));
	philosophers(vars.param.nb_philo, vars.table, &vars.param);
	waiter(&vars);
	return (clean_exit(EXIT_SUCCESS, &vars));
}
