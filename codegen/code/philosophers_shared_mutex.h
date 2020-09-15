/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers_shared_mutex.h                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mrjvs <mrjvs@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 16:00:52 by mrjvs         #+#    #+#                 */
/*   Updated: 2020/09/15 15:27:44 by mrjvs         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_SHARED_MUTEX_H
# define PHILOSOPHERS_SHARED_MUTEX_H

# include <pthread.h>

/*
** t_phil_args, global data shared accross threads/processes
*/

typedef struct	s_phil_args {
	int				amount;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_goal_amount;
	int				eat_goal_counter;
	int				has_died;
	int				crash_exit;
	pthread_mutex_t	logging_lock;
}				t_phil_args;

/*
** t_thread_args, data specific per philosopher thread.
** its passed in on thread creation
*/

typedef struct	s_thread_args
{
	t_phil_args	*args;
	int			id;
	pthread_t	tid;
}				t_thread_args;

#endif
