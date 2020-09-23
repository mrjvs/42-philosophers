/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   state.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mrjvs <mrjvs@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 13:51:59 by mrjvs         #+#    #+#                 */
/*   Updated: 2020/09/23 13:38:50 by mrjvs         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philosophers.h"

static int	init_forks(t_phil_global *global)
{
	int	i;

	global->forks = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * global->amount);
	if (global->forks == NULL)
		return (0);
	i = 0;
	while (i < global->amount)
	{
		if (pthread_mutex_init(global->forks + i, NULL) != 0)
		{
			while (i > 0)
			{
				i--;
				pthread_mutex_destroy(global->forks + i);
			}
			free(global->forks);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	init_phils(t_phil_global *globals)
{
	int	i;

	globals->phil_arr = (t_phil *)malloc(sizeof(t_phil) * globals->amount);
	if (globals->phil_arr == NULL)
		return (0);
	i = 0;
	while (i < globals->amount)
	{
		if (pthread_mutex_init(&(globals->phil_arr[i].eat_lock), NULL) != 0)
		{
			while (i > 0)
			{
				i--;
				pthread_mutex_destroy(&(globals->phil_arr[i].eat_lock));
			}
			free(globals->phil_arr);
			return (0);
		}
		globals->phil_arr[i].globals = globals;
		globals->phil_arr[i].id = i;
		globals->phil_arr[i].eat_countdown = globals->eat_goal;
		i++;
	}
	return (1);
}

int			init_globals(t_phil_global *globals)
{
	int	s;

	if (!init_forks(globals))
		return (0);
	s = (pthread_mutex_init(&(globals->crash_lock), 0) == 0) ? 1 : 0;
	s = (pthread_mutex_init(&(globals->die_lock), 0) == 0) ? ((1 << 1) | s) : s;
	s = (pthread_mutex_init(&(globals->eat_lock), 0) == 0) ? ((1 << 2) | s) : s;
	s = (pthread_mutex_init(&(globals->log_lock), 0) == 0) ? ((1 << 3) | s) : s;
	if (s != 0b1111 || !init_phils(globals))
	{
		destroy_locks(globals, s);
		destroy_forks(globals);
		return (0);
	}
	pthread_mutex_lock(&(globals->die_lock));
	pthread_mutex_lock(&(globals->crash_lock));
	pthread_mutex_lock(&(globals->eat_lock));
	globals->should_exit = 0;
	return (1);
}

void		clear_globals(t_phil_global *globals)
{
	int	i;

	destroy_locks(globals, 0b1111);
	destroy_forks(globals);
	i = 0;
	while (i < globals->amount)
	{
		pthread_mutex_destroy(&(globals->phil_arr[i].eat_lock));
		i++;
	}
	free(globals->phil_arr);
}
