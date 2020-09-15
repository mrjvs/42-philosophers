/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   logger.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mrjvs <mrjvs@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 16:00:38 by mrjvs         #+#    #+#                 */
/*   Updated: 2020/09/15 16:28:23 by mrjvs         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include "philosophers.h"

long long	get_time_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

static int	do_logging(t_phil_args *args, int id, char *suffix, int dolocks)
{
	char	*out;

	if (dolocks)
		lock_logging(args);
	out = phil_make_log(get_time_in_ms(), id + 1, suffix);
	if (out == NULL)
	{
		if (dolocks)
			unlock_logging(args);
		return (0);
	}
	write(1, out, phil_strlen(out));
	free(out);
	if (dolocks)
		unlock_logging(args);
	return (1);
}

int			log_state(enum e_philstate state, int id, t_phil_args *args)
{
	char	*text;

	if (state == Thinking)
		text = "is thinking\n";
	else if (state == Eating)
		text = "is eating\n";
	else if (state == Sleeping)
		text = "is sleeping\n";
	else if (state == Taking)
		text = "has taken a fork\n";
	else if (state == Dying)
		text = "died\n";
	else
		text = "has been behaving unexpectedly\n";
	return (do_logging(args, id, text, state != Dying));
}
