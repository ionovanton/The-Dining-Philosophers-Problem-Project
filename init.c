/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 10:45:07 by srobt             #+#    #+#             */
/*   Updated: 2022/07/05 18:18:17 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	init_forks(t_fork *forks, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philosophers_counter)
	{
		forks[i].number = i + 1;
		if (pthread_mutex_init(&forks[i].mutex, 0))
			return (false);
		i++;
	}
	return (true);
}

static t_bool	init_philosophers(t_philo *philos, t_fork *forks, t_data *data)
{
	pthread_t	ptid;
	int			i;

	i = 0;
	while (i < data->philosophers_counter)
	{
		philos[i].number = i + 1;
		philos[i].mutex_stdout = &data->mutex_stdout;
		if (pthread_mutex_init(&philos[i].mutex_status, 0) \
		|| pthread_mutex_init(&philos[i].mutex_meal_counter, 0))
			return (false);
		philos[i].time_to_die = data->time_to_die;
		philos[i].time_to_eat = data->time_to_eat;
		philos[i].time_to_sleep = data->time_to_sleep;
		philos[i].meal_counter = 0;
		philos[i].meal_goal = data->meal_goal;
		philos[i].fork_left = forks + i;
		philos[i].fork_right = forks + ((i + 1) % data->philosophers_counter);
		if (pthread_create(&ptid, 0, philo_cycle, &philos[i]))
			return (false);
		pthread_detach(ptid);
		i++;
	}
	return (true);
}

t_bool	init_table(t_philo *philos, t_fork *forks, t_data *data)
{	
	if (!init_forks(forks, data) || !init_philosophers(philos, forks, data))
		return (false);
	return (true);
}

t_bool	init_data(int argc, char **argv, t_data *data)
{
	if (argc < 4 || argc > 5)
		return (msg_error(MSG_USAGE, 112));
	data->philosophers_counter = ft_atoi(argv[0]);
	data->time_to_die = ft_atoi(argv[1]);
	data->time_to_eat = ft_atoi(argv[2]);
	data->time_to_sleep = ft_atoi(argv[3]);
	if (argc == 5)
		data->meal_goal = ft_atoi(argv[4]);
	if (data->philosophers_counter > MAX_PHILOS \
	|| data->philosophers_counter < 1 \
	|| data->time_to_die < 0 \
	|| data->time_to_eat < 0 \
	|| data->time_to_sleep < 0 \
	|| (argc == 5 && data->meal_goal < 0))
		return (msg_error(MSG_INVALID_PARAM, 87));
	if (argc != 5)
		data->meal_goal = -1;
	if (pthread_mutex_init(&data->mutex_stdout, 0))
		return (false);
	return (true);
}
