/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:01:42 by flohrel           #+#    #+#             */
/*   Updated: 2021/10/26 21:13:11 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	vars_init(t_vars *vars, t_param *param)
{
	vars->table = NULL;
	param->nb_philo = -1;
	param->time_to_die = -1;
	param->time_to_eat = -1;
	param->time_to_sleep = -1;
	param->nb_eat = -1;
	param->has_ended = false;
	param->start_time = get_ms_time();
	pthread_mutex_init(&param->lock, NULL);
	pthread_mutex_init(&param->message, NULL);
}

int	clean_exit(int ret_value, t_vars *vars)
{
	t_param	*param;

	param = &vars->param;
	pthread_mutex_lock(&param->lock);
	free_philo(vars->table, vars->param.nb_philo);
	pthread_mutex_unlock(&param->lock);
	pthread_mutex_destroy(&param->lock);
	return (ret_value);
}

int	main(int argc, char **argv)
{
	int		i;
	t_vars	vars;

	vars_init(&vars, &vars.param);
	if (parser(argc, argv, &vars.param) == -1)
		return (EXIT_FAILURE);
	if (philo_init(vars.param.nb_philo, &vars.table, &vars.param) == -1)
		return (clean_exit(EXIT_FAILURE, &vars));
	i = vars.param.nb_philo;
	philosophers(vars.param.nb_philo, vars.table);
	waiter(&vars);
	while (i--)
		ms_sleep(vars.param.time_to_eat + vars.param.time_to_sleep);
	return (clean_exit(EXIT_SUCCESS, &vars));
}
