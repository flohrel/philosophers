/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:44:30 by flohrel           #+#    #+#             */
/*   Updated: 2021/10/27 17:38:38 by flohrel          ###   ########.fr       */
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
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>

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
	int32_t			id;
	pthread_t		thread_id;
	pthread_mutex_t	fork;
	int64_t			last_meal;
	int32_t			nb_meal;
	bool			has_finished;
	t_param			*param;
	t_philo			*next;
};

struct	s_param
{
	int32_t			nb_philo;
	int64_t			time_to_die;
	int64_t			time_to_eat;
	int64_t			time_to_sleep;
	int32_t			nb_eat;
	int64_t			start_time;
	bool			has_ended;
	pthread_mutex_t	lock;
	pthread_mutex_t	message;
};

struct	s_vars
{
	t_param			param;
	t_philo			*table;
};

/*
**		FUNCTION
*/
t_philo		*get_last(t_philo *philo);
int			parser(int argc, char **argv, t_param *param);
int64_t		get_ms_time(void);
void		ms_sleep(int64_t value);
void		timestamp_msg(int32_t id, char *msg, int64_t start_time,
				t_param *param);
void		free_philo(t_philo *philo, int32_t nb_philo);
int			philo_init(int32_t nb_philo, t_philo **table, t_param *param);
void		philosophers(int32_t nb_philo, t_philo *philo);
void		waiter(t_vars *vars);

#endif
