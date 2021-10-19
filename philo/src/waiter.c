/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:49:43 by flohrel           #+#    #+#             */
/*   Updated: 2021/10/19 01:36:46 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	waiter(t_vars *vars)
{
	t_param		*param;
	t_philo		*philo;
	int64_t		timestamp;

	param = &vars->param;
	philo = vars->table;
	while (1)
	{
		timestamp = get_ms_time() - param->start_time;
		if ((timestamp - philo->last_meal) > param->time_to_die)
		{
			ms_sleep(5);
			timestamp_msg(philo->id, "died", param->start_time);
			param->has_ended = true;
			break ;
		}
		if (param->nb_philo == 0)
			break ;
		philo = philo->next;
	}
}
