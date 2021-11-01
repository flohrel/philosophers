/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 14:24:17 by flohrel           #+#    #+#             */
/*   Updated: 2021/11/01 23:29:52 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	vars_init(t_philo **table, t_param *param)
{
	*table = NULL;
	param->nb_philo = -1;
	param->time_to_die = -1;
	param->time_to_eat = -1;
	param->time_to_sleep = -1;
	param->nb_meal = -1;
	param->start_time = get_ms_time();
}

void	philo_init(int32_t nb_philo, t_philo **table, t_param *param)
{
	uint32_t	i;
	t_philo		*philo;
	t_philo		*last;

	i = nb_philo + 1;
	while (--i)
	{
		philo = malloc(sizeof(t_philo));
		if (!philo)
			exit(EXIT_FAILURE);
		philo->id = i;
		philo->last_meal = -1;
		philo->is_alive = true;
		philo->param = param;
		philo->next = *table;
		*table = philo;
	}
	last = get_last(*table);
	last->next = *table;
}

void	semaphore_init(t_param *param, int32_t nb_philo)
{
	sem_unlink("/fork");
	sem_unlink("/lock");
	sem_unlink("/message");
	sem_unlink("/end");
	param->fork = sem_open("/fork", O_CREAT, S_IRWXU, nb_philo);
	param->lock = sem_open("/lock", O_CREAT, S_IRWXU, 1);
	param->message = sem_open("/message", O_CREAT, S_IRWXU, 1);
	param->end = sem_open("/end", O_CREAT, S_IRWXU, 1);
}
