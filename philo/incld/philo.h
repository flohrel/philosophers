/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:44:30 by flohrel           #+#    #+#             */
/*   Updated: 2021/10/16 19:16:36 by flohrel          ###   ########.fr       */
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
	uint32_t		id;
	pthread_t		thread_id;
	pthread_mutex_t	fork;
	uint64_t		last_meal;
	int				nb_meal;
	t_param			*param;
	t_philo			*next;
};

struct	s_param
{
	uint32_t	nb_philo;
	uint64_t	time_to_die;
	uint64_t	time_to_eat;
	uint64_t	time_to_sleep;
	uint32_t	nb_eat;
	uint64_t	start_time;
	bool		has_ended;
};

struct	s_vars
{
	t_param		param;
	t_philo		*table;
};

/*
**		FUNCTION
*/
size_t		ft_strlen(const char *s);
int			ft_putchar_fd(int c, int fd);
size_t		ft_putstr_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
int			parser(int argc, char **argv, t_param *param);
uint64_t	get_ms_time(void);
void		ms_sleep(uint64_t value);
void		timestamp_msg(uint32_t id, char *msg, suseconds_t start_time);
void		free_philo(t_philo *philo, uint32_t nb_philo);
int			philo_init(uint32_t nb_philo, t_philo **table, t_param *param);
void		philosophers(uint32_t nb_philo, t_philo *philo);
void		waiter(t_vars *vars);

#endif
