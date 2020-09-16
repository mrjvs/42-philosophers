/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   state.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mrjvs <mrjvs@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 13:51:59 by mrjvs         #+#    #+#                 */
/*   Updated: 2020/09/16 22:45:33 by mrjvs         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philosophers.h"

static int	init_phil(t_phil *phil, t_phil_global *globals, int id)
{
	phil->globals = globals;
	phil->id = id;
	phil->eat_countdown = globals->eat_goal;
	if (pthread_mutex_init(&(phil->eat_lock), NULL))
		return (0);
	return (1);
}

int			init_globals(t_phil_global *globals)
{
	int	i;

	globals->amount = 2;
	globals->eat_goal = 2;
	globals->time_to_die = 6000;
	globals->time_to_eat = 3000;
	globals->time_to_sleep = 2000;
	globals->crash_exit = 0;
	if (!init_forks(globals) ||
		pthread_mutex_init(&(globals->crash_lock), NULL) ||
		pthread_mutex_init(&(globals->die_lock), NULL) ||
		pthread_mutex_init(&(globals->eat_lock), NULL) ||
		pthread_mutex_init(&(globals->log_lock), NULL))
		return (0);
	pthread_mutex_lock(&(globals->die_lock));
	pthread_mutex_lock(&(globals->crash_lock));
	pthread_mutex_lock(&(globals->eat_lock));
	globals->phil_arr = (t_phil *)malloc(sizeof(t_phil) * globals->amount);
	if (globals->phil_arr == NULL)
		return (0);
	i = 0;
	while (i < globals->amount)
	{
		if (!init_phil(globals->phil_arr + i, globals, i))
			return (0);
		i++;
	}
	return (1);
}
