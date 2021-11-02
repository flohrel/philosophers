/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:01:42 by flohrel           #+#    #+#             */
/*   Updated: 2021/11/02 12:23:48 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_vars	vars;
	int		i;

	vars_init(&vars.philo, &vars.param);
	parser(argc, argv, &vars.param);
	semaphore_init(&vars.sem, vars.param.nb_philo);
	philosophers(&vars);
	i = -1;
	while (++i < vars.param.nb_philo)
		kill(vars.pid[i], SIGTERM);
	clean_exit(EXIT_SUCCESS, false, &vars.sem);
}
