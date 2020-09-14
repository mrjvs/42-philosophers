/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mrjvs <mrjvs@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 16:00:52 by mrjvs         #+#    #+#                 */
/*   Updated: 2020/09/14 16:49:56 by mrjvs         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stddef.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>

# define SEM_PERMS S_IRUSR | S_IWUSR | S_IRGRP

# define LLINT_CHARLEN 19
# define INT_CHARLEN 10
# define INT_MAXLEN 2147483647

# define SEM_DIE_LOCK "philosophersDieLock"
# define SEM_EAT_LOCK "philosophersEatLock"
# define SEM_CRASH_LOCK "philosophersCrashLock"
# define SEM_LOGGING_LOCK "philosophersLoggingLock"

enum			e_philstate {
	Eating = 0,
	Sleeping = 1,
	Thinking = 2,
	Taking = 3,
	Dying = 4
};

/*
** t_phil_args, global data shared accross threads/processes
*/

typedef struct	s_phil_args {
	int 			amount;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_goal_amount;
	int				crash_exit;
	sem_t			*logging_lock;
	sem_t			*phil_died_lock;
	sem_t			*phil_eat_lock;
	sem_t			*phil_crash_lock;
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

/*
** t_phil, represent a philosopher
*/

typedef struct	s_phil {
	char		is_dead;
	long		last_meal;
	int			id;
	int			eat_countdown;
	t_phil_args	*args;
	pthread_t	starve_worker;
}				t_phil;

/*
** Philosopher thread functions
*/

void			*create_philosopher(void *arg);
int				start_philosophers(t_phil_args *args);
int				log_state(enum e_philstate state, int id, t_phil_args *args);
int				do_action(t_phil *phil, int activity);
long long		get_time_in_ms(void);
void			start_starve_worker(t_phil *phil);

/*
** Philosopher communication
*/

void			finish_eat_goal(t_phil *phil);
void			trigger_has_died(t_phil *phil);
void			trigger_crash(t_phil *phil);
int				init_args(t_phil_args *args);

/*
** locking
*/

void			lock_logging(t_phil_args *args);
void			unlock_logging(t_phil_args *args);
int				init_locks(t_phil_args *args);
void			destroy_locks(t_phil_args *args);

/*
** string and number utils
*/

int				parse_args(int argc, char *argv[], t_phil_args *args);
size_t			phil_strlen(char *str);
char			*phil_make_log(long long time, int id, char *text);
long			phil_atoi(char *str);

#endif
