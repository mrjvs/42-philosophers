/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lock-mutex.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mrjvs <mrjvs@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 16:00:35 by mrjvs         #+#    #+#                 */
/*   Updated: 2020/09/15 16:35:08 by mrjvs         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** Lock variant: mutex
*/

// TODO this

int		init_locks(t_phil_args *args)
{
	args->logging_lock = sem_open(SEM_LOGGING_LOCK, O_CREAT, SEM_PERMS, 1);
	if (args->logging_lock == SEM_FAILED)
		return (0);
	sem_unlink(SEM_LOGGING_LOCK);
	sem_post(args->logging_lock);
	return (1);
}

void	destroy_locks(t_phil_args *args)
{
	sem_close(args->logging_lock);
}

void	lock_logging(t_phil_args *args)
{
	sem_wait(args->logging_lock);
}

void	unlock_logging(t_phil_args *args)
{
	sem_post(args->logging_lock);
}
