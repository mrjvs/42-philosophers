/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   communication-process.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mrjvs <mrjvs@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 16:00:27 by mrjvs         #+#    #+#                 */
/*   Updated: 2020/09/15 16:22:31 by mrjvs         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** communication variant: process based
*/

void	finish_eat_goal(t_phil *phil)
{
	sem_post(phil->args->phil_eat_lock);
}

void	trigger_has_died(t_phil *phil)
{
	lock_logging(phil->args);
	log_state(Dying, phil->id, phil->args);
	sem_post(phil->args->phil_died_lock);
}

void	trigger_crash(t_phil *phil)
{
	lock_logging(phil->args);
	sem_post(phil->args->phil_crash_lock);
	phil->args->crash_exit = 1;
}

int		init_args(t_phil_args *args)
{
	args->phil_died_lock = sem_open(SEM_DIE_LOCK, O_CREAT, SEM_PERMS, 0);
	args->phil_eat_lock = sem_open(SEM_EAT_LOCK, O_CREAT, SEM_PERMS, 0);
	args->phil_crash_lock =
		sem_open(SEM_CRASH_LOCK, O_CREAT, SEM_PERMS, 0);
	sem_unlink(SEM_DIE_LOCK);
	sem_unlink(SEM_EAT_LOCK);
	sem_unlink(SEM_CRASH_LOCK);
	if (args->phil_died_lock == SEM_FAILED || args->phil_eat_lock == SEM_FAILED || args->phil_crash_lock == SEM_FAILED)
		return (0);
	if (!init_locks(args))
		return (0);
	return (1);
}
