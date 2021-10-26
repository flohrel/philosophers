/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:49:43 by flohrel           #+#    #+#             */
/*   Updated: 2021/10/26 20:53:20 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	waiter(t_vars *vars, int i)
{
	t_param		*param;
	t_philo		*philo;
	int64_t		timestamp;

	param = &vars->param;
	philo = vars->table;
	while (1)
	{
		timestamp = get_ms_time() - param->start_time;
		pthread_mutex_lock(&param->lock);
		if ((timestamp - philo->last_meal) > param->time_to_die)
		{
			printf("%ldms %d died\n", timestamp, philo->id);
			param->has_ended = true;
			pthread_mutex_unlock(&param->lock);
			while (i--)
				ms_sleep(param->time_to_eat + param->time_to_sleep);
			break ;
		}
		if (param->nb_philo == 0)
			break ;
		pthread_mutex_unlock(&param->lock);
		philo = philo->next;
	}
}
