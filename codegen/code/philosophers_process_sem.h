/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers_process_sem.h                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mrjvs <mrjvs@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 16:00:52 by mrjvs         #+#    #+#                 */
/*   Updated: 2020/09/15 18:29:43 by mrjvs         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_PROCESS_SEM_H
# define PHILOSOPHERS_PROCESS_SEM_H

# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>

# define SEM_PERMS 416

# define SEM_DIE_LOCK "philosophersDieLock"
# define SEM_FORKS "philosophersForks"
# define SEM_EAT_LOCK "philosophersEatLock"
# define SEM_CRASH_LOCK "philosophersCrashLock"
# define SEM_LOGGING_LOCK "philosophersLoggingLock"

/*
** t_phil_args, global data shared accross threads/processes
*/

typedef struct	s_phil_args {
	int				amount;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_goal_amount;
	int				crash_exit;
	sem_t			*logging_lock;
	sem_t			*phil_died_lock;
	sem_t			*phil_eat_lock;
	sem_t			*phil_crash_lock;
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
	pid_t		tid;
}				t_thread_args;

void			stop_philosophers(t_thread_args *tid, t_phil_args *args);

#endif
