/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:44:30 by flohrel           #+#    #+#             */
/*   Updated: 2021/11/01 23:29:37 by flohrel          ###   ########.fr       */
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
# define THREADS_MAX	4096

/*
**		TYPE
*/
typedef struct s_philo	t_philo;
typedef struct s_param	t_param;
typedef struct s_vars	t_vars;

struct	s_philo
{
	int32_t		id;
	pid_t		pid;
	int32_t		nb_meal;
	int64_t		last_meal;
	bool		is_alive;
	t_param		*param;
	t_philo		*next;
};

struct	s_param
{
	int32_t	nb_philo;
	int64_t	time_to_die;
	int64_t	time_to_eat;
	int64_t	time_to_sleep;
	int32_t	nb_meal;
	int64_t	start_time;
	sem_t	*lock;
	sem_t	*message;
	sem_t	*fork;
	sem_t	*end;
};

/*
**		FUNCTION
*/
void		vars_init(t_philo **table, t_param *param);
void		parser(int argc, char **argv, t_param *param);
void		semaphore_init(t_param *param, int32_t nb_philo);
void		philo_init(int32_t nb_philo, t_philo **table, t_param *param);
void		philosophers(int32_t nb_philo, t_philo *philo);
int64_t		get_ms_time(void);
void		ms_sleep(int64_t value);
void		timestamp_msg(char *msg, t_philo *philo, t_param *param);
t_philo		*get_last(t_philo *philo);
void		clean_exit(int ret_value, bool is_child, t_philo *table);
void		free_philo(t_philo *philo, int32_t nb_philo);

#endif
