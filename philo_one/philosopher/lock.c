/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lock.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mrjvs <mrjvs@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 16:00:35 by mrjvs         #+#    #+#                 */
/*   Updated: 2020/09/14 16:00:36 by mrjvs         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** Lock variant: mutex
*/

int		init_locks(t_phil_args *args)
{
	if (pthread_mutex_init(&(args->logging_lock), NULL) != 0)
		return (0);
	return (1);
}

void	destroy_locks(t_phil_args *args)
{
	pthread_mutex_destroy(&(args->logging_lock));
}

void	lock_logging(t_phil_args *args)
{
	pthread_mutex_lock(&(args->logging_lock));
}

void	unlock_logging(t_phil_args *args)
{
	pthread_mutex_unlock(&(args->logging_lock));
}
