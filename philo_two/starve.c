/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   starve.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mrjvs <mrjvs@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 15:09:19 by mrjvs         #+#    #+#                 */
/*   Updated: 2020/09/23 15:49:04 by mrjvs         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philosophers.h"

static void	*starve_routine(void *args)
{
	t_phil	*phil;

	phil = (t_phil *)args;
	while (1)
	{
		sem_wait(phil->eat_lock);
		if (get_time() > phil->last_ate + phil->globals->time_to_die)
		{
			sem_wait(phil->globals->log_lock);
			if (phil->globals->should_exit == 0)
				phil_log(phil, Dielog);
			phil->globals->should_exit = 1;
			sem_post(phil->globals->die_lock);
		}
		sem_post(phil->eat_lock);
		usleep(1000);
	}
	return (NULL);
}

int			start_starve_worker(t_phil *phil)
{
	pthread_t	tid;

	phil->last_ate = get_time();
	if (pthread_create(&tid, NULL,
		starve_routine, (void *)(phil)) != 0)
		return (0);
	pthread_detach(tid);
	return (1);
}
