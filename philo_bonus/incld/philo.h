/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:44:30 by flohrel           #+#    #+#             */
/*   Updated: 2021/11/02 11:50:16 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*
**		LIB
*/
# include <unistd.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <stdbool.h>
# include <signal.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>

/*
**		MACRO
*/
# define PROCESS_MAX	1024

/*
**		TYPE
*/
typedef struct s_sem	t_sem;
typedef struct s_philo	t_philo;
typedef struct s_param	t_param;
typedef struct s_vars	t_vars;

struct	s_philo
{
	int32_t		id;
	int32_t		nb_meal;
	int64_t		last_meal;
};

struct	s_param
{
	int32_t	nb_philo;
	int64_t	time_to_die;
	int64_t	time_to_eat;
	int64_t	time_to_sleep;
	int32_t	nb_meal;
	int64_t	start_time;
};

struct	s_sem
{
	sem_t	*lock;
	sem_t	*lock2;
	sem_t	*message;
	sem_t	*fork;
	sem_t	*end;
};

struct	s_vars
{
	t_sem	sem;
	t_philo	philo;
	t_param	param;
	pid_t	pid[PROCESS_MAX];
};

/*
**		FUNCTION
*/
void	vars_init(t_philo *philo, t_param *param);
void	parser(int argc, char **argv, t_param *param);
void	semaphore_init(t_sem *sem, int32_t nb_philo);
void	philosophers(t_vars *vars);
int64_t	get_ms_time(void);
void	ms_sleep(int64_t value);
void	timestamp_msg(char *msg, t_philo *philo, t_param *param, t_sem *sem);
void	clean_exit(int ret_value, bool is_child, t_sem *sem);

#endif
