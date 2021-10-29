/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 06:58:18 by flohrel           #+#    #+#             */
/*   Updated: 2021/10/29 13:42:02 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo, t_param *param)
{
	sem_wait(param->fork);
	timestamp_msg(philo->id, "has taken a fork", param->start_time, param);
	sem_wait(param->fork);
	timestamp_msg(philo->id, "has taken a fork", param->start_time, param);
	timestamp_msg(philo->id, "is eating", param->start_time, param);
	ms_sleep(param->time_to_eat);
	sem_wait(param->lock);
	philo->last_meal = get_ms_time() - param->start_time;
	philo->nb_meal++;
	sem_post(param->lock);
	sem_post(param->fork);
	sem_post(param->fork);
}

void	*observe(void *arg)
{
	t_philo	*philo;
	t_param	*param;

	philo = arg;
	param = philo->param;
	sem_wait(param->end);
	sem_wait(param->lock);
	philo->has_finished = true;
	param->has_ended = true;
	param->nb_philo--;
	sem_post(param->end);
	sem_post(param->lock);
	return (NULL);
}

void	routine(t_philo *philo, t_param *param)
{
	pthread_t	thread_id;

	pthread_create(&thread_id, NULL, observe, philo);
	pthread_detach(thread_id);
	pthread_create(&thread_id, NULL, waiter, philo);
	pthread_detach(thread_id);
	if (philo->id % 2 == 0)
		ms_sleep(5);
	while (1)
	{
		sem_wait(param->lock);
		if (philo->has_finished == true)
		{
			sem_post(param->lock);
			break ;
		}
		sem_post(param->lock);
		eat(philo, param);
		timestamp_msg(philo->id, "is sleeping", param->start_time, param);
		ms_sleep(param->time_to_sleep);
		timestamp_msg(philo->id, "is thinking", param->start_time, param);
	}
	clean_exit(EXIT_SUCCESS, true, philo);
	exit(EXIT_SUCCESS);
}

int	philosophers(int32_t nb_philo, t_philo *philo)
{
	int		i;
	pid_t	pid;

	i = nb_philo;
	while (i--)
	{
		pid = fork();
		if (pid == -1)
			return (clean_exit(EXIT_FAILURE, false, philo));
		else if (pid == 0)
			routine(philo, philo->param);
		else if (pid)
			philo->pid = pid;
		philo = philo->next;
	}
	return (0);
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
