#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include "boot.h"

# define STARVE_WORKER_SLEEP_MS 1

enum e_philstate {
	Eating = 0,
	Sleeping = 1,
	Thinking = 2,
	Taking = 3,
	Dying = 4
};

typedef struct	s_phil {
	char		is_dead;
	long		last_meal;
	int			id;
	int			eat_countdown;
	t_phil_args	*args;
	pthread_t	starve_worker;
}				t_phil;

void		*create_philosopher(void *arg);
int			log_state(enum e_philstate state, int id);
int			do_action(t_phil *phil, int activity);
long long	get_time_in_ms(void);
void		start_starve_worker(t_phil *phil);
int			should_run(t_phil *phil);

#endif
