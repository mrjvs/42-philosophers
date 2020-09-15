/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   forks-mutex.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mrjvs <mrjvs@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 16:00:33 by mrjvs         #+#    #+#                 */
/*   Updated: 2020/09/15 16:56:54 by mrjvs         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
** lock variant: mutex
*/

static void init_destroy_forks(t_phil_args *args, int end)
{
    int i;

    i = 0;
    while (i < end)
    {
        pthread_mutex_destroy(args->forks + i);
        i++;
    }
    free(args->forks);
}

int     	init_forks(t_phil_args *args)
{
    int i;

    args->forks =
        (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * args->amount);
    if (args->forks == NULL)
        return (0);
    i = 0;
    while (i < args->amount)
    {
        if (pthread_mutex_init(args->forks + i, NULL) != 0)
        {
            init_destroy_forks(args, i);
            return (0);
        }
        i++;
    }
	return (1);
}

int	        destroy_forks(t_phil_args *args)
{
	init_destroy_forks(args, args->amount);
	return (1);
}

int	        take_fork(t_phil *phil, enum e_forkside side)
{
    int offset;

    if (side == LeftSide)
        offset = phil->id;
    else
        offset = (phil->id - 1 < 0) ? (args->amount - 1) : (phil->id - 1);
    pthread_mutex_lock(args->forks + offset);
	if (!log_state(Taking, phil->id, phil->args))
	{
		trigger_crash(phil);
		return (0);
	}
	return (1);
}

int	        return_fork(t_phil *phil, enum e_forkside side)
{
	int offset;

    if (side == LeftSide)
        offset = phil->id;
    else
        offset = (phil->id - 1 < 0) ? (args->amount - 1) : (phil->id - 1);
    pthread_mutex_unlock(args->forks + offset);
	return (1);
}
