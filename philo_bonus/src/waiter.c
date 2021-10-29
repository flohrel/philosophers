/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:49:43 by flohrel           #+#    #+#             */
/*   Updated: 2021/10/29 13:43:10 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*waiter(void *arg)
{
	int64_t	timestamp;
	t_philo	*philo;
	t_param	*param;

	philo = arg;
	param = philo->param;
	while (1)
	{
		timestamp = get_ms_time() - param->start_time;
		sem_wait(param->lock);
		if (!philo->has_finished
			&& (timestamp - philo->last_meal) > param->time_to_die)
		{
			sem_post(param->end);
			printf("%ldms %d died\n", timestamp, philo->id);
			break ;
		}
		if (param->nb_philo == 0)
			break ;
		sem_post(param->lock);
	}
	philo->has_finished = true;
	param->nb_philo--;
	sem_post(param->lock);
	return (NULL);
}
