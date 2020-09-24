/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mrjvs <mrjvs@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 12:41:52 by mrjvs         #+#    #+#                 */
/*   Updated: 2020/09/24 10:06:15 by mrjvs         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/types.h>
# include <pthread.h>
# include <semaphore.h>

# define PHILSEM 0644

enum							e_logtype {
	Dielog,
	Takelog,
	Sleeplog,
	Eatlog,
	ThinkLog
};

enum							e_exittype {
	Dieexit,
	Crashexit,
	Goalreachedexit
};

typedef struct s_phil_global	t_phil_global;

typedef struct					s_phil {
	int					id;
	sem_t				*eat_lock;
	unsigned long long	last_ate;
	int					eat_countdown;
	t_phil_global		*globals;
}								t_phil;

struct							s_phil_global
{
	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;
	int				amount;
	int				eat_goal;
	int				crash_exit;
	int				should_exit;
	sem_t			*forks;
	enum e_exittype	exit_cause;
	sem_t			*log_lock;
	sem_t			*die_lock;
	sem_t			*crash_lock;
	sem_t			*eat_lock;
	t_phil			*phil_arr;
};

typedef struct					s_phil_thread {
	int				id;
	t_phil_global	*globals;
	pid_t			tid;
}								t_phil_thread;

int								phil_log(t_phil *phil, enum e_logtype type);
unsigned long long				get_time(void);
int								init_globals(t_phil_global *globals);
int								seat_philosophers(t_phil_global *globals);
int								start_starve_worker(t_phil *phil);

void							phil_eat(t_phil *phil);
void							yeet_forks(t_phil *phil);
void							weaponize_forks(t_phil *phil);
void							phil_sleep(t_phil *phil);
void							clear_globals(t_phil_global *globals);
ssize_t							phil_putnbr(unsigned long long n);
size_t							phil_strlen(char *str);
int								parse_args(int argc, char *argv[],\
											t_phil_global *globals);
int								destroy_forks(t_phil_global *global);
void							destroy_locks(t_phil_global *globals);
int								destroy_phil(t_phil *arr, char *c);
int								inside_while_loop(t_phil_global *globals,\
									t_phil_thread *threads, int *i);
void							*philosopher_routine(void *args);

#endif
