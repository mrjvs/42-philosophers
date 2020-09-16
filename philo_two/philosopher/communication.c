/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   communication-thread.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mrjvs <mrjvs@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 16:00:27 by mrjvs         #+#    #+#                 */
/*   Updated: 2020/09/15 17:44:20 by mrjvs         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** communication variant: thread based
*/

void	finish_eat_goal(t_phil *phil)
{
	phil->args->eat_goal_counter--;
}

void	trigger_has_died(t_phil *phil)
{
	if (!log_state(Dying, phil->id, phil->args))
		phil->args->crash_exit = 1;
	phil->args->has_died = 1;
}

void	trigger_crash(t_phil *phil)
{
	lock_logging(phil->args);
	phil->args->crash_exit = 1;
}

int		should_run(t_phil_args *args)
{
	return (
		args->crash_exit != 1 &&
		args->has_died != 1 &&
		args->eat_goal_counter != 0);
}

int		init_args(t_phil_args *args)
{
	args->has_died = 0;
	args->eat_goal_counter = args->amount;
	return (init_locks(args));
}
