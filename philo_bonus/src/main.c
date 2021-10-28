/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:01:42 by flohrel           #+#    #+#             */
/*   Updated: 2021/10/28 14:55:18 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	int		i;
	t_vars	vars;

	vars_init(&vars, &vars.param);
	if (parser(argc, argv, &vars.param) == -1)
		return (EXIT_FAILURE);
	semaphore_init(&vars.param, vars.param.nb_philo);
	if (philo_init(vars.param.nb_philo, &vars.table, &vars.param) == -1)
		return (clean_exit(EXIT_FAILURE, &vars));
	i = vars.param.nb_philo;
	philosophers(vars.param.nb_philo, vars.table, &vars);
//	waiter(&vars);
	while (i--)
		ms_sleep(vars.param.time_to_eat + vars.param.time_to_sleep);
	sem_close(vars.param.fork);
	sem_close(vars.param.lock);
	sem_close(vars.param.message);
	return (clean_exit(EXIT_SUCCESS, &vars));
}
