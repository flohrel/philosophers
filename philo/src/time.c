/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 06:12:08 by flohrel           #+#    #+#             */
/*   Updated: 2021/10/16 19:17:20 by flohrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_ms_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	timestamp_msg(uint32_t id, char *msg, suseconds_t start_time)
{
	ft_putnbr_fd((get_ms_time() - start_time), STDOUT_FILENO);
	ft_putstr_fd("ms ", STDOUT_FILENO);
	ft_putnbr_fd(id, STDOUT_FILENO);
	ft_putchar_fd(' ', STDOUT_FILENO);
	ft_putstr_fd(msg, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

void	ms_sleep(uint64_t value)
{
	uint64_t	start;

	start = get_ms_time();
	while ((get_ms_time() - start) < value)
	{
		usleep(1);
	}
}
