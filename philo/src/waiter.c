/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:49:43 by flohrel           #+#    #+#             */
/*   Updated: 2021/10/16 18:35:33 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*observe(void *arg)
{
	t_vars	*vars;
	t_param	*param;
	t_philo	*philo;

	vars = arg;
	param = &vars->param;
	philo = vars->table;
	while (1)
	{
		if ((get_usec_time() - philo->last_meal) >= param->time_to_die)
		{
			timestamp_msg(philo->id, "died", param->start_time);
			break ;
		}
		philo = philo->next;
	}
	return (NULL);
}

void	waiter(t_vars *vars)
{
	pthread_t	thread_id;

	pthread_create(&thread_id, NULL, observe, vars);
	pthread_join(thread_id, NULL);
}
