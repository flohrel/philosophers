/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 06:58:18 by flohrel           #+#    #+#             */
/*   Updated: 2021/10/21 11:14:34 by flohrel          ###   ########.fr       */
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
		philo->param = param;
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
	timestamp_msg(philo->id, "has taken a fork", param->start_time);
	pthread_mutex_lock(&philo->next->fork);
	timestamp_msg(philo->id, "has taken a fork", param->start_time);
	timestamp_msg(philo->id, "is eating", param->start_time);
	ms_sleep(param->time_to_eat);
	philo->last_meal = get_ms_time() - param->start_time;
	philo->nb_meal++;
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_param	*param;

	philo = arg;
	param = philo->param;
	if (philo->id % 2 == 0)
		ms_sleep(1);
	while (param->has_ended == false)
	{
		eat(philo, param);
		if (philo->nb_meal == param->nb_eat)
		{
			param->nb_philo--;
			break ;
		}
		timestamp_msg(philo->id, "is sleeping", param->start_time);
		ms_sleep(param->time_to_sleep);
		timestamp_msg(philo->id, "is thinking", param->start_time);
	}
	return (NULL);
}

void	philosophers(int32_t nb_philo, t_philo *philo)
{
	int		i;
	pid_t	pid;

	i = nb_philo;
	while (i--)
	{
		pid = fork();
		if (pid == -1)
			clean_exit();				// TODO
		else if (pid != 0)
			philo->pid = pid;
		else
			routine();
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
		free(philo);
		philo = next;
	}
}
