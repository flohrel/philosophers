/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 10:48:05 by flohrel           #+#    #+#             */
/*   Updated: 2021/11/01 23:42:14 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_exit(int ret_value, bool is_child, t_philo *table)
{
	t_param	*param;

	param = table->param;
	sem_close(param->fork);
	sem_close(param->lock);
	sem_close(param->message);
	sem_close(param->end);
	if (!is_child)
	{
		sem_unlink("/fork");
		sem_unlink("/lock");
		sem_unlink("/message");
		sem_unlink("/end");
	}
	free_philo(table, param->nb_philo);
	exit(ret_value);
}

void	timestamp_msg(char *msg, t_philo *philo, t_param *param)
{
	int64_t	timestamp;

	sem_wait(param->lock);
	if (philo->is_alive == true)
	{
		sem_wait(param->message);
		timestamp = get_ms_time() - param->start_time;
		printf("%ldms %d %s\n", timestamp, philo->id, msg);
		sem_post(param->message);
	}
	sem_post(param->lock);
}

void	free_philo(t_philo *philo, int32_t nb_philo)
{
	int32_t	i;
	t_philo	*next;

	i = -1;
	while (++i < nb_philo)
	{
		next = philo->next;
		free(philo);
		philo = next;
	}
}

t_philo	*get_last(t_philo *philo)
{
	while (philo->next != NULL)
		philo = philo->next;
	return (philo);
}
