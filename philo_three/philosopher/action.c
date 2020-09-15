/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   action.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mrjvs <mrjvs@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 16:00:25 by mrjvs         #+#    #+#                 */
/*   Updated: 2020/09/15 12:44:12 by mrjvs         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philosophers.h"

static int	do_eat(t_phil *phil)
{
	if (!take_fork(phil, LeftSide) || !take_fork(phil, RightSide))
		return (0);
	phil->last_meal = get_time_in_ms();
	if (phil->eat_countdown > 0)
	{
		phil->eat_countdown--;
		if (phil->eat_countdown == 0)
			finish_eat_goal(phil);
	}
	return (1);
}

int			do_action(t_phil *phil, int activity)
{
	int	sleep_time;

	if (activity == Thinking)
		sleep_time = 0;
	else if (activity == Sleeping)
	{
		if (!return_fork(phil, LeftSide) || !return_fork(phil, RightSide))
			return (0);
		sleep_time = phil->args->time_to_sleep;
	}
	else if (activity == Eating)
	{
		sleep_time = phil->args->time_to_eat;
		if (!do_eat(phil))
			return (0);
	}
	if (!log_state(activity, phil->id, phil->args))
		return (0);
	usleep(1000 * sleep_time);
	return (1);
}
