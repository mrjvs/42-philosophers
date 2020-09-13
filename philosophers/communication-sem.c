#include "philosopher.h"

void	finish_eat_goal(t_phil *phil) {
	sem_post(phil->args->phil_eat_lock);
}

void	trigger_has_died(t_phil *phil) {
	sem_post(phil->args->phil_died_lock);
}

void	trigger_crash(t_phil *phil) {
	sem_post(phil->args->phil_crash_lock);
	phil->args->crash_exit = 1;
}

int		should_run(t_phil *phil) {
	return (!phil->is_dead && !phil->args->crash_exit);
}

void	init_args(t_phil_args *args) {
	args->phil_died_lock = sem_init(SEM_DIE_LOCK, 1, 0); // !
	args->phil_eat_lock = sem_init(SEM_EAT_LOCK, 1, 0);
	args->phil_crash_lock = sem_init(SEM_CRASH_LOCK, 1, 0);
	sem_unlink(SEM_DIE_LOCK);
	sem_unlink(SEM_EAT_LOCK);
	sem_unlink(SEM_CRASH_LOCK);
}
