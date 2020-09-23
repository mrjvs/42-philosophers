/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   destroy.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mrjvs <mrjvs@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/23 13:38:53 by mrjvs         #+#    #+#                 */
/*   Updated: 2020/09/23 16:26:09 by mrjvs         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philosophers.h"

int		destroy_forks(t_phil_global *global)
{
	sem_destroy(global->forks);
	return (1);
}

void	destroy_locks(t_phil_global *globals)
{
	if (globals->crash_lock != SEM_FAILED)
		sem_destroy(globals->crash_lock);
	if (globals->die_lock != SEM_FAILED)
		sem_destroy(globals->die_lock);
	if (globals->eat_lock != SEM_FAILED)
		sem_destroy(globals->eat_lock);
	if (globals->log_lock != SEM_FAILED)
		sem_destroy(globals->log_lock);
}

int		destroy_phil(t_phil *arr, char *c)
{
	if (c != NULL)
		free(c);
	if (arr != NULL)
		free(arr);
	return (0);
}
