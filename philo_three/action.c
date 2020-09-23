/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   action.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mrjvs <mrjvs@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 15:37:43 by mrjvs         #+#    #+#                 */
/*   Updated: 2020/09/23 15:49:26 by mrjvs         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "philosophers.h"

void	weaponize_forks(t_phil *phil)
{
	sem_wait(phil->globals->forks);
	phil_log(phil, Takelog);
	sem_wait(phil->globals->forks);
	phil_log(phil, Takelog);
}

void	yeet_forks(t_phil *phil)
{
	sem_post(phil->globals->forks);
	sem_post(phil->globals->forks);
}

void	phil_eat(t_phil *phil)
{
	sem_wait(phil->eat_lock);
	sem_wait(phil->globals->log_lock);
	phil_log(phil, Eatlog);
	phil->last_ate = get_time();
	if (phil->eat_countdown > 0)
	{
		phil->eat_countdown--;
		if (phil->eat_countdown == 0)
			sem_post(phil->globals->eat_lock);
		else
			sem_post(phil->globals->log_lock);
	}
	else
		sem_post(phil->globals->log_lock);
	sem_post(phil->eat_lock);
	usleep(phil->globals->time_to_eat * 1000);
}

void	phil_sleep(t_phil *phil)
{
	phil_log(phil, Sleeplog);
	usleep(phil->globals->time_to_sleep * 1000);
}
