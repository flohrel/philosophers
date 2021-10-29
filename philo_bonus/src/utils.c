/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 10:48:05 by flohrel           #+#    #+#             */
/*   Updated: 2021/10/29 12:10:09 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	clean_exit(int ret_value, bool is_child, t_philo *table)
{
	t_param	*param;

	param = table->param;
	sem_close(param->fork);
	sem_close(param->lock);
	sem_close(param->message);
	if (!is_child)
	{
		sem_unlink("/fork");
		sem_unlink("/lock");
		sem_unlink("/message");
	}
	free_philo(table, param->nb_philo);
	return (ret_value);
}

t_philo	*get_last(t_philo *philo)
{
	while (philo->next != NULL)
		philo = philo->next;
	return (philo);
}
