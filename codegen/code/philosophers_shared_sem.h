/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers_shared_sem.h                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mrjvs <mrjvs@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 16:00:52 by mrjvs         #+#    #+#                 */
/*   Updated: 2020/09/15 16:26:07 by mrjvs         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_SHARED_SEM_H
# define PHILOSOPHERS_SHARED_SEM_H

# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>

# define SEM_PERMS 416

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
	sem_t			*logging_lock;
	sem_t			*forks;
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
