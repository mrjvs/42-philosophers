/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   action.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mrjvs <mrjvs@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 15:37:43 by mrjvs         #+#    #+#                 */
/*   Updated: 2020/09/17 18:30:20 by mrjvs         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "philosophers.h"

void	weaponize_forks(t_phil *phil)
{
	pthread_mutex_lock(&(phil->globals->forks[phil->id]));
	phil_log(phil, Takelog);
	pthread_mutex_lock(&(phil->globals->forks
		[(phil->id + 1) % phil->globals->amount]));
	phil_log(phil, Takelog);
}

void	yeet_forks(t_phil *phil)
{
	pthread_mutex_unlock(&(phil->globals->forks[phil->id]));
	pthread_mutex_unlock(&(phil->globals->forks
		[(phil->id + 1) % phil->globals->amount]));
}

void	phil_eat(t_phil *phil)
{
	pthread_mutex_lock(&(phil->eat_lock));
	pthread_mutex_lock(&(phil->globals->log_lock));
	phil_log(phil, Eatlog);
	phil->last_ate = get_time();
	if (phil->eat_countdown > 0)
	{
		phil->eat_countdown--;
		if (phil->eat_countdown == 0)
			pthread_mutex_unlock(&(phil->globals->eat_lock));
		else
			pthread_mutex_unlock(&(phil->globals->log_lock));
	}
	else
		pthread_mutex_unlock(&(phil->globals->log_lock));
	pthread_mutex_unlock(&(phil->eat_lock));
	usleep(phil->globals->time_to_eat * 1000);
}

void	phil_sleep(t_phil *phil)
{
	phil_log(phil, Sleeplog);
	usleep(phil->globals->time_to_sleep * 1000);
}
