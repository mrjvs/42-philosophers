#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

enum e_philstate {
	Eating = 0,
	Sleeping = 1,
	Thinking = 2,
	Taking = 3,
	Dying = 4
};

void	*create_philosopher(void *arg);
void	log_state(enum e_philstate state, int id);
void	do_action(int id, int activity);

#endif
