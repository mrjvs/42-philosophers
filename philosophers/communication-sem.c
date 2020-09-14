#include <fcntl.h>
#include <sys/stat.h>
#include "philosopher.h"
#define SEM_PERMS S_IRUSR | S_IWUSR | S_IRGRP

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

int		init_args(t_phil_args *args) {
	args->phil_died_lock = sem_open(SEM_DIE_LOCK, O_CREAT, SEM_PERMS, 0);
	args->phil_eat_lock = sem_open(SEM_EAT_LOCK, O_CREAT, SEM_PERMS, 0);
	args->phil_crash_lock = sem_open(SEM_CRASH_LOCK, O_CREAT, SEM_PERMS, 0);
	sem_unlink(SEM_DIE_LOCK);
	sem_unlink(SEM_EAT_LOCK);
	sem_unlink(SEM_CRASH_LOCK);
	if (args->phil_died_lock == SEM_FAILED || args->phil_eat_lock == SEM_FAILED || args->phil_crash_lock == SEM_FAILED)
		return (0);
	return (1);
}
