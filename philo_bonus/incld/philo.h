/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:44:30 by flohrel           #+#    #+#             */
/*   Updated: 2021/10/29 13:42:58 by flohrel          ###   ########.fr       */
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
	bool		has_finished;
	t_param		*param;
	t_philo		*next;
};

struct	s_param
{
	int32_t	nb_philo;
	int64_t	time_to_die;
	int64_t	time_to_eat;
	int64_t	time_to_sleep;
	int32_t	nb_eat;
	int64_t	start_time;
	bool	has_ended;
	sem_t	*lock;
	sem_t	*message;
	sem_t	*fork;
	sem_t	*end;
};

struct	s_vars
{
	t_param	param;
	t_philo	*table;
};

/*
**		FUNCTION
*/
void		vars_init(t_vars *vars, t_param *param);
void		semaphore_init(t_param *param, int32_t nb_philo);
int			philo_init(int32_t nb_philo, t_philo **table, t_param *param);
t_philo		*get_last(t_philo *philo);
int			parser(int argc, char **argv, t_param *param);
int64_t		get_ms_time(void);
void		ms_sleep(int64_t value);
void		timestamp_msg(int32_t id, char *msg, int64_t start_time,
				t_param *param);
void		free_philo(t_philo *philo, int32_t nb_philo);
int			philosophers(int32_t nb_philo, t_philo *philo);
void		*waiter(void *arg);
int			clean_exit(int ret_value, bool is_child, t_philo *table);

#endif
