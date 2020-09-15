/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mrjvs <mrjvs@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 16:00:52 by mrjvs         #+#    #+#                 */
/*   Updated: 2020/09/15 15:56:33 by mrjvs         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stddef.h>
# include <pthread.h>

# include "philosophers_process_sem.h"

# define LLINT_CHARLEN 19
# define INT_CHARLEN 10
# define INT_MAXLEN 2147483647

enum			e_philstate {
	Eating = 0,
	Sleeping = 1,
	Thinking = 2,
	Taking = 3,
	Dying = 4
};

enum			e_forkside {
	LeftSide,
	RightSide
};

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

int				should_run(t_phil_args *args);
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
** forks
*/

int				init_forks(t_phil_args *args);
int				destroy_forks(t_phil_args *args);
int				take_fork(t_phil *phil, enum e_forkside side);
int				return_fork(t_phil *phil, enum e_forkside side);

/*
** string and number utils
*/

int				parse_args(int argc, char *argv[], t_phil_args *args);
size_t			phil_strlen(char *str);
char			*phil_make_log(long long time, int id, char *text);
long			phil_atoi(char *str);

#endif
