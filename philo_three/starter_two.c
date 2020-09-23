/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   starter_two.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mrjvs <mrjvs@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/23 18:23:45 by mrjvs         #+#    #+#                 */
/*   Updated: 2020/09/23 18:33:23 by mrjvs         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "philosophers.h"

int	inside_while_loop(t_phil_global *globals, t_phil_thread *threads, int *i)
{
	threads[*i].id = *i;
	threads[*i].globals = globals;
	threads[*i].tid = fork();
	if (threads[*i].tid == -1)
	{
		sem_wait(globals->log_lock);
		sem_post(globals->die_lock);
		globals->crash_exit = 1;
		return (0);
	}
	else if (threads[*i].tid == 0)
	{
		philosopher_routine((void *)(threads + *i));
		exit(1);
	}
	usleep(100);
	(*i)++;
	return (1);
}
