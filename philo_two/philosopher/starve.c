/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   starve.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mrjvs <mrjvs@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 16:00:44 by mrjvs         #+#    #+#                 */
/*   Updated: 2020/09/14 16:00:45 by mrjvs         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philosophers.h"

static void	*starve_checker(void *arg)
{
	t_phil	*phil;

	phil = (t_phil *)arg;
	while (1)
	{
		if (phil->last_meal + phil->args->time_to_die < get_time_in_ms())
		{
			trigger_has_died(phil);
			break ;
		}
		usleep(1000);
	}
}

void		start_starve_worker(t_phil *phil)
{
	if (pthread_create(&(phil->starve_worker),
		NULL, starve_checker, (void *)phil) != 0)
	{
		trigger_crash(phil);
		return ;
	}
	pthread_detach(phil->starve_worker);
}
