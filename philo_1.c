/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:11:56 by srobt             #+#    #+#             */
/*   Updated: 2022/07/05 18:01:51 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_update_data(t_philo *p)
{
	pthread_mutex_lock(&p->mutex_status);
	gettimeofday(&p->time_last_meal, 0);
	pthread_mutex_unlock(&p->mutex_status);
	pthread_mutex_lock(&p->mutex_meal_counter);
	p->meal_counter++;
	pthread_mutex_unlock(&p->mutex_meal_counter);
	pthread_mutex_lock(&p->mutex_meal_goal_achieved);
	if (p->meal_counter == p->meal_goal)
		p->meal_goal_achieved = true;
	pthread_mutex_lock(&p->mutex_meal_goal_achieved);
}

static void	philo_eat(t_philo *p)
{
	t_fork	*min;
	t_fork	*max;

	min = p->fork_right;
	max = p->fork_left;
	if (p->fork_left->number < p->fork_right->number)
	{
		min = p->fork_left;
		max = p->fork_right;
	}
	pthread_mutex_lock(&min->mutex);
	msg_status(p, FORK);
	pthread_mutex_lock(&max->mutex);
	msg_status(p, FORK);
	msg_status(p, EAT);
	philo_update_data(p);
	time_usleep(p->time_to_eat);
	pthread_mutex_unlock(&max->mutex);
	pthread_mutex_unlock(&min->mutex);
}

static void	philo_sleep(t_philo *p)
{
	msg_status(p, SLEEP);
	time_usleep(p->time_to_sleep);
}

static void	philo_think(t_philo *p)
{
	msg_status(p, THINK);
	usleep(200);
}

void	*philo_cycle(void *data)
{
	t_philo	*p;

	p = (t_philo *)data;
	gettimeofday(&p->time_start_const, 0);
	p->time_last_meal = p->time_start_const;
	if ((p->number % 2) == 0)
		usleep(100);
	while (true)
	{
		philo_eat(p);
		pthread_mutex_lock(&p->mutex_meal_counter);
		if (p->meal_counter == p->meal_goal)
			return (NULL);
		pthread_mutex_unlock(&p->mutex_meal_counter);
		philo_sleep(p);
		philo_think(p);
	}
	return (NULL);
}
