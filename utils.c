/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 10:47:42 by srobt             #+#    #+#             */
/*   Updated: 2022/07/05 18:35:27 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_atoi(const char *s)
{
	long long	res;
	long long	sign;

	sign = 1;
	res = 0;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s == ' ')
		s++;
	while (*s >= '0' && *s <= '9')
	{
		res *= 10;
		res += *s - '0';
		s++;
	}
	if (!(*s >= '0' && *s <= '9') && (*s != '\0'))
		return (-1);
	return (res * sign);
}

t_bool	ft_check(int argc, char **argv)
{
	int	ms;
	int	i;
	int	j;

	i = 0;
	while (i < argc)
	{
		ms = 0;
		j = 0;
		while (argv[i][j])
		{
			if ((argv[i][j] < '0' || argv[i][j] > '9') \
			&& argv[i][j] != '-' && argv[i][j] != '+')
				return (0);
			if (argv[i][j] == '-' || argv[i][j] == '+')
				ms++;
			j++;
		}
		if (ms > 1)
			return (0);
		i++;
	}
	return (1);
}

t_bool	msg_error(char *msg, int length)
{
	write(2, msg, length);
	return (false);
}

void	msg_status(t_philo *p, int status)
{
	pthread_mutex_lock(p->mutex_stdout);
	if (status == EAT)
		printf("%lu %d %s\n", \
		time_get_running(p->time_start_const), p->number, MSG_EAT);
	else if (status == SLEEP)
		printf("%lu %d %s\n", \
		time_get_running(p->time_start_const), p->number, MSG_SLEEP);
	else if (status == THINK)
		printf("%lu %d %s\n", \
		time_get_running(p->time_start_const), p->number, MSG_THINK);
	else if (status == FORK)
		printf("%lu %d %s\n", \
		time_get_running(p->time_start_const), p->number, MSG_FORK);
	else if (status == DIED)
	{
		printf("%lu %d %s\n", \
		time_get_running(p->time_start_const), p->number, MSG_DIED);
		return ;
	}
	pthread_mutex_unlock(p->mutex_stdout);
}
