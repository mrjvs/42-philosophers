/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   starter-process.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mrjvs <mrjvs@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 16:00:42 by mrjvs         #+#    #+#                 */
/*   Updated: 2020/09/15 18:17:06 by mrjvs         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "philosophers.h"

/*
** communication variant: process based
*/

static void	*crash_worker(void *arg)
{
	t_phil_args	*args;

	args = (t_phil_args *)arg;
	sem_wait(args->phil_crash_lock);
	lock_logging(args);
	args->crash_exit = 1;
	sem_post(args->phil_died_lock);
}

static void	*eat_worker(void *arg)
{
	int			i;
	t_phil_args	*args;

	args = (t_phil_args *)arg;
	i = 0;
	while (i < args->amount)
	{
		sem_wait(args->phil_eat_lock);
		i++;
	}
	lock_logging(args);
	sem_post(args->phil_died_lock);
}

static int	start_workers(t_phil_args *args)
{
	pthread_t	tid;

	if (pthread_create(&tid, NULL, crash_worker, (void *)args) != 0)
		return (0);
	pthread_detach(tid);
	if (pthread_create(&tid, NULL, eat_worker, (void *)args) != 0)
		return (0);
	pthread_detach(tid);
	return (1);
}

static void	do_thing(t_thread_args *tid, t_phil_args *args, int *i)
{
	tid->id = *i;
	tid->args = args;
	tid->tid = fork();
	if (tid->tid == 0)
	{
		create_philosopher((void *)tid);
		exit(0);
	}
	else if (tid->tid < 0)
	{
		lock_logging(args);
		args->crash_exit = 1;
		sem_post(args->phil_died_lock);
	}
	(*i)++;
}

int			start_philosophers(t_phil_args *args)
{
	int				i;
	t_thread_args	*tid;

	if (!start_workers(args))
		return (0);
	tid = (t_thread_args *)malloc(args->amount * sizeof(t_thread_args));
	if (tid == NULL)
		return (0);
	i = 0;
	while (i < args->amount)
		do_thing(tid + i, args, &i);
	sem_wait(args->phil_died_lock);
	stop_philosophers(tid, args);
	return (1);
}
