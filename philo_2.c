/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 16:33:30 by srobt             #+#    #+#             */
/*   Updated: 2022/07/05 16:57:17 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	philo_is_dead(t_philo *p)
{
	t_timeval	current;

	gettimeofday(&current, 0);
	pthread_mutex_lock(&p->mutex_status);
	if (time_get_diff(current, p->time_last_meal) >= p->time_to_die)
	{
		msg_status(p, DIED);
		pthread_mutex_unlock(&p->mutex_status);
		return (true);
	}
	pthread_mutex_unlock(&p->mutex_status);
	return (false);
}

static t_bool	philo_is_all_full(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	if (data->meal_goal == -1)
		return (false);
	while (i < data->philosophers_counter)
	{
		pthread_mutex_lock(&philos[i].mutex_meal_goal_achieved);
		if (philos[i].meal_goal_achieved == false)
			return (false);
		pthread_mutex_unlock(&philos[i].mutex_meal_goal_achieved);
		i++;
	}
	return (true);
}

int	philo_monitor(t_philo *philos, t_data *data)
{
	int	i;

	while (true)
	{
		i = 0;
		while (i < data->philosophers_counter)
		{
			if (philo_is_dead(&philos[i]) || philo_is_all_full(philos, data))
				return (FAIL);
			i++;
		}
	}
	return (SUCCESS);
}
