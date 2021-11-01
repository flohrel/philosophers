/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 06:58:18 by flohrel           #+#    #+#             */
/*   Updated: 2021/11/02 00:03:44 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock_end(t_param *param)
{
	int	i;

	i = param->nb_philo;
	while (i--)
		sem_post(param->end);
}

void	*waiter(void *arg)
{
	t_philo	*philo;
	t_param	*param;
	int64_t	timestamp;

	philo = arg;
	param = philo->param;
	while (1)
	{
		timestamp = get_ms_time() - param->start_time;
		sem_wait(param->lock);
		if ((timestamp - philo->last_meal) > param->time_to_die)
		{
			printf("%ldms %d died\n", timestamp, philo->id);
			unlock_end(param);
			break ;
		}
		if (philo->nb_meal == param->nb_meal)
		{
			philo->is_alive = false;
			break ;
		}
		sem_post(param->lock);
	}
	sem_post(param->lock);
	return (NULL);
}

void	*leaver(void *arg)
{
	t_philo	*philo;
	t_param	*param;

	philo = arg;
	param = philo->param;
	sem_wait(param->end);
	sem_wait(param->lock);
	philo->is_alive = false;
	sem_post(param->lock);
	printf("leaving...\n");
	ms_sleep(1000);
	return (NULL);
}

void	routine(t_philo *philo, t_param *param)
{
	pthread_t	thread1;
	pthread_t	thread2;

	pthread_create(&thread1, NULL, waiter, philo);
	pthread_detach(thread1);
	pthread_create(&thread2, NULL, leaver, philo);
	pthread_detach(thread2);
	while (1)
	{
		sem_wait(param->lock);
		if (philo->is_alive == false)
		{
			sem_post(param->lock);
			break ;
		}
		sem_post(param->lock);
		ms_sleep(1000);
	}
	clean_exit(EXIT_SUCCESS, true, philo);
}

void	philosophers(int32_t nb_philo, t_philo *philo)
{
	int32_t	i;
	pid_t	pid;

	i = nb_philo;
	while (i--)
	{
		pid = fork();
		if (pid == -1)
			clean_exit(EXIT_FAILURE, false, philo);
		else if (pid == 0)
			routine(philo, philo->param);
		else
			philo->pid = pid;
		philo = philo->next;
	}
}
