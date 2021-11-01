/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:01:42 by flohrel           #+#    #+#             */
/*   Updated: 2021/11/02 00:06:22 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_param	param;
	t_philo	*table;
	int		count;

	vars_init(&table, &param);
	parser(argc, argv, &param);
	count = param.nb_philo;
	semaphore_init(&param, param.nb_philo);
	philo_init(param.nb_philo, &table, &param);
	philosophers(param.nb_philo, table);
	while (count--)
		waitpid(-1, NULL, 0);
	clean_exit(EXIT_SUCCESS, false, table);
}
