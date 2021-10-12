/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:01:42 by flohrel           #+#    #+#             */
/*   Updated: 2021/10/12 17:26:28 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	clean_exit(int ret_val, t_vars *vars)
{
	(void)vars;
	return (ret_val);
}

void	init_vars(t_vars *vars, t_param *param)
{
	(void)vars;
	param->nb_philo = -1;
	param->time_to_die = -1;
	param->time_to_eat = -1;
	param->time_to_sleep = -1;
	param->nb_eat = -1;
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	init_vars(&vars, &vars.param);
	if (parse_args(argc, argv, &vars.param) == -1)
		return (EXIT_FAILURE);
	return (0);
}
