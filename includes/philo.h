/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobt <srobt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 23:47:57 by srobt             #+#    #+#             */
/*   Updated: 2022/07/05 18:27:44 by srobt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

// Code
# define SUCCESS	0
# define FAIL		1

// Philosopher status
# define EAT		1
# define SLEEP		2
# define THINK		3
# define FORK		4
# define DIED		5

// Status messages
# define MSG_EAT	"is eating"
# define MSG_SLEEP	"is sleeping"
# define MSG_THINK	"is thinking"
# define MSG_FORK 	"has taken a fork"
# define MSG_DIED	"died"

// Other
# define MSG_USAGE			"Usage: number_of_philosophers time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n" // 112
# define MSG_INVALID_PARAM	"Each parameter should be a positive number\n\
Philosophers number cannot be more than 200\n" // 87
# define MAX_PHILOS			200

typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_timeval;

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef struct s_data
{
	int				philosophers_counter;
	t_timeval		time_start_const;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		meal_goal;
	t_mutex			mutex_stdout;
}	t_data;

typedef struct s_fork
{
	int		number;
	t_mutex	mutex;
}	t_fork;

typedef struct s_philo
{
	t_fork		*fork_right;
	t_fork		*fork_left;
	t_mutex		*mutex_stdout;
	t_mutex		mutex_status;
	t_mutex		mutex_meal_counter;
	t_mutex		mutex_meal_goal_achieved;
	t_timeval	time_start_const;
	t_timeval	time_last_meal;
	long long	time_to_die;
	long long	time_to_eat;
	long long	time_to_sleep;
	t_bool		meal_goal_achieved;
	long long	meal_goal;
	long long	meal_counter;
	int			number;
}	t_philo;

// Driver
int			philo_monitor(t_philo *philos, t_data *data);
void		*philo_cycle(void *data);

// Init
t_bool		init_data(int argc, char **argv, t_data *data);
t_bool		init_table(t_philo *philos, t_fork *forks, t_data *data);

// Utils
long long	ft_atoi(const char *s);
t_bool		ft_check(int argc, char **argv);
t_bool		msg_error(char *msg, int length);
void		msg_status(t_philo *p, int status);
void		time_usleep(unsigned long time);
long		time_get_running(t_timeval time_start_const);
long		time_get_diff(t_timeval tv1, t_timeval tv2);

#endif /* PHILO_H */
