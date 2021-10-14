/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 06:12:08 by flohrel           #+#    #+#             */
/*   Updated: 2021/10/14 06:54:51 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ms_sleep(int value)
{
	struct timeval	start;
	struct timeval	cur;

	gettimeofday(&start, NULL);
	cur = start;
	value *= 1000;
	while ((cur.tv_usec - start.tv_usec) < value)
	{
		usleep(500);
		gettimeofday(&cur, NULL);
	}
}
