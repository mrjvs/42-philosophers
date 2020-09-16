/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   logger.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mrjvs <mrjvs@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 12:41:11 by mrjvs         #+#    #+#                 */
/*   Updated: 2020/09/16 16:42:05 by mrjvs         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h> // !
#include "philosophers.h"

static int	write_phil_log(t_phil *phil, char *suffix, int dolocks)
{
	if (dolocks)
		pthread_mutex_lock(&(phil->globals->log_lock));
	//TODO remove printf
	printf("%llu %i %s\n", get_time(), phil->id + 1, suffix);
	if (dolocks)
		pthread_mutex_unlock(&(phil->globals->log_lock));
	return (1);
}

int			phil_log(t_phil *phil, enum e_logtype type)
{
	char	*suffix;

	if (type == Dielog)
		suffix = "has died";
	else if (type == Takelog)
		suffix = "has taken a fork";
	else if (type == Sleeplog)
		suffix = "is sleeping";
	else if (type == Eatlog)
		suffix = "is eating";
	else if (type == ThinkLog)
		suffix = "is thinking";
	else
		suffix = "has been behaving unexpectedly";
	return (write_phil_log(phil, suffix, type != Dielog));
}
