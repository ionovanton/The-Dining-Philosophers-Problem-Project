/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 12:25:31 by srobt             #+#    #+#             */
/*   Updated: 2022/07/05 16:53:56 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_get_running(t_timeval time_start_const)
{
	t_timeval	current;

	gettimeofday(&current, 0);
	return ((current.tv_sec - time_start_const.tv_sec) * 1000 \
	+ (current.tv_usec - time_start_const.tv_usec) / 1000);
}

long	time_get_diff(t_timeval tv1, t_timeval tv2)
{
	return (((tv1.tv_sec - tv2.tv_sec) * 1000) + \
	((tv1.tv_usec - tv2.tv_usec) / 1000));
}

static unsigned long	time_get(void)
{
	t_timeval		current;
	unsigned long	value;

	gettimeofday(&current, 0);
	value = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	return (value);
}

void	time_usleep(unsigned long us)
{
	unsigned long	start;

	start = time_get();
	while ((time_get() - start) < us)
	{
		usleep(100);
	}	
}
