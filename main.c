/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 10:43:35 by srobt             #+#    #+#             */
/*   Updated: 2022/07/05 17:39:31 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo	philos[MAX_PHILOS];
	t_fork	forks[MAX_PHILOS];
	t_data	data;

	if (!init_data(--argc, ++argv, &data) || !init_table(philos, forks, &data))
		return (FAIL);
	usleep(200);
	return (philo_monitor(philos, &data));
}
