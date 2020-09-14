/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   entry.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mrjvs <mrjvs@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 16:00:30 by mrjvs         #+#    #+#                 */
/*   Updated: 2020/09/14 16:00:30 by mrjvs         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_phil	make_phil_state(t_phil_args *args, int id)
{
	t_phil	phil;

	phil.is_dead = 0;
	phil.last_meal = get_time_in_ms();
	phil.id = id;
	phil.args = args;
	phil.eat_countdown = args->eat_goal_amount;
	phil.starve_worker = -1;
	return (phil);
}

/*
** main philosopher look, this does all the actions in a loop forever
** until main thread terminates
*/

static void		main_loop(t_phil *phil)
{
	int	activity;

	activity = 0;
	while (1)
	{
		if (!do_action(phil, activity))
			trigger_crash(phil);
		activity++;
		if (activity > 2)
			activity = 0;
	}
}

void			*create_philosopher(void *arg)
{
	t_phil	phil;

	phil = make_phil_state(
		((t_thread_args *)arg)->args,
		((t_thread_args *)arg)->id);
	start_starve_worker(&phil);
	main_loop(&phil);
}
