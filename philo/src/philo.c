/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 06:58:18 by flohrel           #+#    #+#             */
/*   Updated: 2021/10/14 07:16:21 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	*get_last(t_philo *philo)
{
	while (philo->next != NULL)
		philo = philo->next;
	return (philo);
}

int	philo_init(uint32_t nb_philo, t_philo **table)
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
		philo->next = *table;
		*table = philo;
	}
	last = get_last(*table);
	last->next = *table;
	return (0);
}

void	routine(void *arg)
{
	t_vars	*vars;

	vars = arg;

}

void	launch(uint32_t nb_philo, t_philo *philo, t_vars *vars)
{
	int	i;

	i = -1;
	while (++i < nb_philo)
	{
		pthread_create(philo->thread_id, NULL, routine, vars);
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
		free(philo);
		philo = next;
	}
}

