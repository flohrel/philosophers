/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 06:58:18 by flohrel           #+#    #+#             */
/*   Updated: 2021/10/27 17:08:04 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_init(int32_t nb_philo, t_philo **table, t_param *param)
{
	uint32_t	i;
	t_philo		*philo;
	t_philo		*last;

	i = nb_philo + 1;
	while (--i)
	{
		philo = malloc(sizeof(t_philo));
		if (!philo)
			return (-1);
		philo->id = i;
		philo->last_meal = -1;
		philo->has_finished = false;
		philo->param = param;
		pthread_mutex_init(&philo->fork, NULL);
		philo->next = *table;
		*table = philo;
	}
	last = get_last(*table);
	last->next = *table;
	return (0);
}

void	eat(t_philo *philo, t_param *param)
{
	pthread_mutex_lock(&philo->fork);
	timestamp_msg(philo->id, "has taken a fork", param->start_time, param);
	pthread_mutex_lock(&philo->next->fork);
	timestamp_msg(philo->id, "has taken a fork", param->start_time, param);
	timestamp_msg(philo->id, "is eating", param->start_time, param);
	pthread_mutex_lock(&param->lock);
	philo->last_meal = get_ms_time() - param->start_time;
	philo->nb_meal++;
	pthread_mutex_unlock(&param->lock);
	ms_sleep(param->time_to_eat);
	pthread_mutex_unlock(&philo->next->fork);
	pthread_mutex_unlock(&philo->fork);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_param	*param;

	philo = arg;
	param = philo->param;
	if (philo->id % 2 == 0)
		ms_sleep(5);
	while (1)
	{
		pthread_mutex_lock(&param->lock);
		if ((philo->nb_meal == param->nb_eat) || (param->has_ended == true))
		{
			philo->has_finished = true;
			param->nb_philo--;
			pthread_mutex_unlock(&param->lock);
			break ;
		}
		pthread_mutex_unlock(&param->lock);
		eat(philo, param);
		timestamp_msg(philo->id, "is sleeping", param->start_time, param);
		ms_sleep(param->time_to_sleep);
		timestamp_msg(philo->id, "is thinking", param->start_time, param);
	}
	return (NULL);
}

void	philosophers(int32_t nb_philo, t_philo *philo)
{
	int	i;

	i = nb_philo;
	while (i--)
	{
		pthread_create(&philo->thread_id, NULL, routine, philo);
		pthread_detach(philo->thread_id);
		philo = philo->next;
	}
}

void	free_philo(t_philo *philo, int32_t nb_philo)
{
	int32_t	i;
	t_philo	*next;

	i = -1;
	while (++i < nb_philo)
	{
		next = philo->next;
		pthread_mutex_destroy(&philo->fork);
		free(philo);
		philo = next;
	}
}
