/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   starter.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mrjvs <mrjvs@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:24:16 by mrjvs         #+#    #+#                 */
/*   Updated: 2020/09/23 15:32:19 by mrjvs         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "philosophers.h"

void		*philosopher_routine(void *args)
{
	t_phil	*phil;

	phil = ((t_phil_thread *)args)->globals->phil_arr +
		((t_phil_thread *)args)->id;
	if (!start_starve_worker(phil))
	{
		pthread_mutex_lock(&(phil->globals->log_lock));
		pthread_mutex_unlock(&(phil->globals->crash_lock));
		return (NULL);
	}
	while (1)
	{
		weaponize_forks(phil);
		phil_eat(phil);
		yeet_forks(phil);
		phil_sleep(phil);
		phil_log(phil, ThinkLog);
	}
	return (NULL);
}

static void	*eat_goal_worker(void *args)
{
	int				i;
	t_phil_global	*globals;

	i = 0;
	globals = (t_phil_global *)args;
	while (i < globals->amount)
	{
		pthread_mutex_lock(&(globals->eat_lock));
		i++;
		if (i < globals->amount)
			pthread_mutex_unlock(&(globals->log_lock));
	}
	pthread_mutex_unlock(&(globals->die_lock));
	return (NULL);
}

static void	*crash_worker(void *args)
{
	t_phil_global	*globals;

	globals = (t_phil_global *)args;
	pthread_mutex_lock(&(globals->crash_lock));
	globals->crash_exit = 1;
	pthread_mutex_unlock(&(globals->die_lock));
	return (NULL);
}

static int	start_workers(t_phil_global *globals)
{
	pthread_t	tid;

	if (pthread_create(&tid, NULL,
		eat_goal_worker, (void *)globals) != 0)
		return (0);
	pthread_detach(tid);
	if (pthread_create(&tid, NULL,
		crash_worker, (void *)globals) != 0)
		return (0);
	pthread_detach(tid);
	return (1);
}

int			seat_philosophers(t_phil_global *globals)
{
	t_phil_thread	*threads;
	int				i;

	threads = (t_phil_thread *)malloc(sizeof(t_phil_thread) * globals->amount);
	if (threads == NULL || !start_workers(globals))
		return (0);
	i = 0;
	while (i < globals->amount)
	{
		threads[i].id = i;
		threads[i].globals = globals;
		if (pthread_create(&(threads[i].tid), NULL,
			philosopher_routine, (void *)(threads + i)) != 0)
		{
			pthread_mutex_lock(&(globals->log_lock));
			free(threads);
			return (0);
		}
		pthread_detach(threads[i].tid);
		usleep(100);
		i++;
	}
	pthread_mutex_lock(&(globals->die_lock));
	free(threads);
	return (globals->crash_exit == 1 ? 0 : 1);
}
