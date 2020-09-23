/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   destroy.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mrjvs <mrjvs@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/23 13:38:53 by mrjvs         #+#    #+#                 */
/*   Updated: 2020/09/23 14:17:40 by mrjvs         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philosophers.h"

int		destroy_forks(t_phil_global *global)
{
	int	i;

	i = 0;
	while (i > global->amount)
	{
		pthread_mutex_destroy(global->forks + i);
		i++;
	}
	free(global->forks);
	return (1);
}

void	destroy_locks(t_phil_global *globals, int s)
{
	if ((s & (1 << 0)) == 1 << 0)
		pthread_mutex_destroy(&(globals->crash_lock));
	if ((s & (1 << 1)) == 1 << 1)
		pthread_mutex_destroy(&(globals->die_lock));
	if ((s & (1 << 2)) == 1 << 2)
		pthread_mutex_destroy(&(globals->eat_lock));
	if ((s & (1 << 3)) == 1 << 3)
		pthread_mutex_destroy(&(globals->log_lock));
}
