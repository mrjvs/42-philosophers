/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   forks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mrjvs <mrjvs@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 16:00:33 by mrjvs         #+#    #+#                 */
/*   Updated: 2020/09/15 12:42:12 by mrjvs         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** lock variant: semaphore
*/

int	init_forks(t_phil_args *args)
{
	args->forks = sem_open(SEM_FORKS, O_CREAT, SEM_PERMS, args->amount);
	if (args->forks == SEM_FAILED)
		return (0);
	sem_unlink(SEM_FORKS);
	return (1);
}

int	destroy_forks(t_phil_args *args)
{
	sem_close(args->forks);
	return (1);
}

int	take_fork(t_phil *phil, enum e_forkside side)
{
	(void)side;
	sem_wait(phil->args->forks);
	if (!log_state(Taking, phil->id, phil->args))
	{
		trigger_crash(phil);
		return (0);
	}
	return (1);
}

int	return_fork(t_phil *phil, enum e_forkside side)
{
	(void)side;
	sem_post(phil->args->forks);
	return (1);
}
