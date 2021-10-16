/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 06:58:18 by flohrel           #+#    #+#             */
/*   Updated: 2021/10/16 18:38:30 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	*get_last(t_philo *philo)
{
	while (philo->next != NULL)
		philo = philo->next;
	return (philo);
}

int	philo_init(uint32_t nb_philo, t_philo **table, t_param *param)
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
		philo->is_alive = true;
		philo->param = param;
		pthread_mutex_init(&philo->fork, NULL);
		philo->next = *table;
		*table = philo;
	}
	last = get_last(*table);
	last->next = *table;
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_param	*param;

	philo = arg;
	param = philo->param;
	while (philo->is_alive)
	{
		pthread_mutex_lock(&philo->fork);
		timestamp_msg(philo->id, "has taken a fork", param->start_time);
		pthread_mutex_lock(&philo->next->fork);
		timestamp_msg(philo->id, "has taken a fork", param->start_time);
		timestamp_msg(philo->id, "is eating", param->start_time);
		ms_sleep(param->time_to_eat);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		philo->last_meal = get_usec_time();
		timestamp_msg(philo->id, "is sleeping", param->start_time);
		ms_sleep(param->time_to_sleep);
		timestamp_msg(philo->id, "is thinking", param->start_time);
	}
	return (NULL);
}

void	philosophers(uint32_t nb_philo, t_philo *philo)
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

void	free_philo(t_philo *philo, uint32_t nb_philo)
{
	uint32_t	i;
	t_philo		*next;

	i = -1;
	while (++i < nb_philo)
	{
		next = philo->next;
		pthread_mutex_destroy(&philo->fork);
		free(philo);
		philo = next;
	}
}
