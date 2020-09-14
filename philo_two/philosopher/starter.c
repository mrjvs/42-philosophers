/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   starter.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mrjvs <mrjvs@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 16:00:42 by mrjvs         #+#    #+#                 */
/*   Updated: 2020/09/14 16:00:43 by mrjvs         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "philosophers.h"

/*
** communication variant: thread based
*/

static void	wait_philosophers(t_phil_args *args)
{
	while (should_run(args))
		usleep(1000);
}

int			start_philosophers(t_phil_args *args)
{
	int				i;
	t_thread_args	*tid;

	tid = (t_thread_args *)malloc(args->amount * sizeof(t_thread_args));
	if (tid == NULL)
		return (0);
	i = 0;
	while (i < args->amount)
	{
		tid[i].id = i;
		tid[i].args = args;
		if (pthread_create(&(tid[i].tid),
			NULL, create_philosopher, (void *)(&(tid[i]))) != 0)
		{
			lock_logging(args);
			args->crash_exit = 1;
		}
		else
			pthread_detach(tid[i].tid);
		i++;
	}
	wait_philosophers(args);
	free(tid);
	return (1);
}
