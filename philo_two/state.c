/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   state.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mrjvs <mrjvs@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 13:51:59 by mrjvs         #+#    #+#                 */
/*   Updated: 2020/09/23 16:25:08 by mrjvs         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "philosophers.h"

static int	init_forks(t_phil_global *global)
{
	global->forks = sem_open("philosophersForksSem", O_CREAT,\
	PHIL_SEM_MODE, global->amount);
	if (global->forks == SEM_FAILED)
		return (0);
	sem_unlink("philosophersForksSem");
	return (1);
}

static char	*make_phil_string(int id)
{
	char	*c;
	int		i;

	c = malloc(13);
	if (c == NULL)
		return (NULL);
	memset(c, '0', 12);
	c[0] = 'p';
	c[1] = 'h';
	c[12] = '\0';
	i = 11;
	while (id > 9)
	{
		c[i] = '0' + (id % 10);
		id = id / 10;
		i--;
	}
	c[i] = '0' + (id % 10);
	return (c);
}

static int	init_phils(t_phil_global *globals)
{
	int		i;
	char	*c;

	globals->phil_arr = (t_phil *)malloc(sizeof(t_phil) * globals->amount);
	if (globals->phil_arr == NULL)
		return (0);
	i = 0;
	while (i < globals->amount)
	{
		c = make_phil_string(i);
		if (c == NULL)
			return (destroy_phil(globals->phil_arr, c));
		globals->phil_arr[i].eat_lock = sem_open(c, O_CREAT, PHIL_SEM_MODE, 1);
		if (globals->phil_arr[i].eat_lock == SEM_FAILED)
			return (destroy_phil(globals->phil_arr, c));
		sem_unlink(c);
		free(c);
		globals->phil_arr[i].globals = globals;
		globals->phil_arr[i].id = i;
		globals->phil_arr[i].eat_countdown = globals->eat_goal;
		i++;
	}
	return (1);
}

int			init_globals(t_phil_global *globals)
{
	if (!init_forks(globals))
		return (0);
	globals->crash_lock = sem_open("philosophersCrashLock", O_CREAT, PHIL_SEM_MODE, 0);
	globals->die_lock = sem_open("philosophersDieLock", O_CREAT, PHIL_SEM_MODE, 0);
	globals->eat_lock = sem_open("philosophersEatLock", O_CREAT, PHIL_SEM_MODE, 0);
	globals->log_lock = sem_open("philosophersLogLock", O_CREAT, PHIL_SEM_MODE, 1);
	sem_unlink("philosophersCrashLock");
	sem_unlink("philosophersDieLock");
	sem_unlink("philosophersEatLock");
	sem_unlink("philosophersLogLock");
	if (globals->crash_lock == SEM_FAILED ||
		globals->die_lock == SEM_FAILED ||
		globals->eat_lock == SEM_FAILED ||
		globals->log_lock == SEM_FAILED ||
		!init_phils(globals))
	{
		destroy_locks(globals);
		destroy_forks(globals);
		return (0);
	}
	globals->should_exit = 0;
	return (1);
}

void		clear_globals(t_phil_global *globals)
{
	destroy_locks(globals);
	destroy_forks(globals);
	free(globals->phil_arr);
}
