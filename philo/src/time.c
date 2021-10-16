/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 06:12:08 by flohrel           #+#    #+#             */
/*   Updated: 2021/10/16 18:36:17 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

suseconds_t	get_usec_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_usec);
}

void	timestamp_msg(uint32_t id, char *msg, suseconds_t start_time)
{
	ft_putnbr_fd((get_usec_time() - start_time) / 1000, STDOUT_FILENO);
	ft_putstr_fd("ms ", STDOUT_FILENO);
	ft_putnbr_fd(id, STDOUT_FILENO);
	ft_putchar_fd(' ', STDOUT_FILENO);
	ft_putstr_fd(msg, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

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
