/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 06:12:08 by flohrel           #+#    #+#             */
/*   Updated: 2021/11/02 16:09:56 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int64_t	get_ms_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	timestamp_msg(int32_t id, char *msg, int64_t start_time, t_param *param)
{
	int64_t	timestamp;

	pthread_mutex_lock(&param->lock);
	if (param->has_ended == false)
	{
		timestamp = get_ms_time() - start_time;
		printf("%lldms %d %s\n", timestamp, id, msg);
	}
	pthread_mutex_unlock(&param->lock);
}

void	ms_sleep(int64_t value)
{
	int64_t	start;

	start = get_ms_time();
	while ((get_ms_time() - start) < value)
	{
		usleep(500);
	}
}
