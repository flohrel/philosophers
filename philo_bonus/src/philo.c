/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 06:58:18 by flohrel           #+#    #+#             */
/*   Updated: 2021/11/02 16:29:22 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*waiter(void *arg)
{
	t_philo	*philo;
	t_param	*param;
	int64_t	timestamp;

	philo = &((t_vars *)arg)->philo;
	param = &((t_vars *)arg)->param;
	while (1)
	{
		timestamp = get_ms_time() - param->start_time;
		sem_wait(((t_vars *)arg)->sem.lock);
		if ((timestamp - philo->last_meal) > param->time_to_die)
		{
			timestamp_msg("died", philo, param, &((t_vars *)arg)->sem);
			sem_wait(((t_vars *)arg)->sem.message);
			exit(0);
		}
		if ((param->nb_meal != -1) && (philo->nb_meal == param->nb_meal))
		{
			sem_post(((t_vars *)arg)->sem.end);
			break ;
		}
		sem_post(((t_vars *)arg)->sem.lock);
	}
	sem_post(((t_vars *)arg)->sem.lock);
	return (NULL);
}

void	eat(t_philo *philo, t_param *param, t_sem *sem)
{
	sem_wait(sem->fork);
	timestamp_msg("has taken a fork", philo, param, sem);
	sem_wait(sem->fork);
	timestamp_msg("has taken a fork", philo, param, sem);
	timestamp_msg("is eating", philo, param, sem);
	sem_wait(sem->lock);
	philo->last_meal = get_ms_time() - param->start_time;
	philo->nb_meal++;
	sem_post(sem->lock);
	ms_sleep(param->time_to_eat);
	sem_post(sem->fork);
	sem_post(sem->fork);
}

void	routine(t_vars *vars)
{
	pthread_t	tid;

	pthread_create(&tid, NULL, waiter, vars);
	if (vars->philo.id % 2 == 0)
		ms_sleep(5);
	while (1)
	{
		eat(&vars->philo, &vars->param, &vars->sem);
		timestamp_msg("is sleeping", &vars->philo, &vars->param, &vars->sem);
		ms_sleep(vars->param.time_to_sleep);
		timestamp_msg("is thinking", &vars->philo, &vars->param, &vars->sem);
	}
}

void	*meal_observer(void *arg)
{
	t_vars	*vars;
	t_sem	*sem;
	t_param	*param;
	int		i;

	vars = arg;
	sem = &vars->sem;
	param = &vars->param;
	i = -1;
	while (++i < param->nb_philo)
		sem_wait(sem->end);
	i = -1;
	while (++i < param->nb_philo)
		kill(vars->pid[i], SIGTERM);
	return (NULL);
}

void	philosophers(t_vars *vars)
{
	int32_t		i;
	pid_t		pid;
	pthread_t	tid;

	i = -1;
	while (++i < vars->param.nb_philo)
	{
		pid = fork();
		if (pid == -1)
			clean_exit(EXIT_FAILURE, false, &vars->sem);
		else if (pid == 0)
		{
			vars->philo.id = i + 1;
			routine(vars);
			i = vars->param.nb_philo;
		}
		else
			vars->pid[i] = pid;
	}
	if (vars->param.nb_meal != -1)
	{
		pthread_create(&tid, NULL, meal_observer, vars);
		pthread_detach(tid);
	}
	waitpid(-1, NULL, 0);
}
