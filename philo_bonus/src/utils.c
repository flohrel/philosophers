/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 10:48:05 by flohrel           #+#    #+#             */
/*   Updated: 2021/11/02 16:23:38 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_exit(int ret_value, bool is_child, t_sem *sem)
{
	sem_close(sem->fork);
	sem_close(sem->lock);
	sem_close(sem->message);
	sem_close(sem->end);
	if (!is_child)
	{
		sem_unlink("/fork");
		sem_unlink("/lock");
		sem_unlink("/message");
		sem_unlink("/end");
	}
	exit(ret_value);
}

void	timestamp_msg(char *msg, t_philo *philo, t_param *param, t_sem *sem)
{
	int64_t	timestamp;

	sem_wait(sem->message);
	timestamp = get_ms_time() - param->start_time;
	printf("%lldms %d %s\n", timestamp, philo->id, msg);
	sem_post(sem->message);
}
