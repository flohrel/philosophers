/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 14:24:17 by flohrel           #+#    #+#             */
/*   Updated: 2021/11/02 11:49:58 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	vars_init(t_philo *philo, t_param *param)
{
	param->nb_philo = -1;
	param->time_to_die = -1;
	param->time_to_eat = -1;
	param->time_to_sleep = -1;
	param->nb_meal = -1;
	param->start_time = get_ms_time();
	philo->last_meal = -1;
	philo->nb_meal = 0;
}

void	semaphore_init(t_sem *sem, int32_t nb_philo)
{
	sem_unlink("/fork");
	sem_unlink("/lock");
	sem_unlink("/message");
	sem_unlink("/end");
	sem->fork = sem_open("/fork", O_CREAT, S_IRWXU, nb_philo);
	sem->lock = sem_open("/lock", O_CREAT, S_IRWXU, 1);
	sem->message = sem_open("/message", O_CREAT, S_IRWXU, 1);
	sem->end = sem_open("/end", O_CREAT, S_IRWXU, 0);
}
