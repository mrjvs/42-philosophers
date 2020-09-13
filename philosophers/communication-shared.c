#include "philosopher.h"

// semaphore states all need semaphore posts
void	finish_eat_goal(t_phil *phil) {
	phil->args->eat_goal_counter--;
}

void	trigger_has_died(t_phil *phil) {
	phil->args->has_died = 1;
}

// this will need extra work in semaphore states
void	trigger_crash(t_phil *phil) {
	phil->args->crash_exit = 1;
}

int		should_run(t_phil *phil) {
	return (!phil->is_dead && phil->args->eat_goal_counter != 0 && !phil->args->crash_exit);
}

void	init_args(t_phil_args *args) {
	args->has_died = 0;
	args->eat_goal_counter = args->amount;
}
