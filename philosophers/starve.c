#include <stddef.h>
#include <pthread.h>
#include <unistd.h>
#include "philosopher.h"

/*
** starve checker thread
** checks if philosopher has starved every millisecond (STARVE_WORKER_SLEEP_MS)
*/
static void	*starve_checker(void *arg) {
	t_phil	*phil;

	phil = (t_phil *)arg;
	while (should_run(phil)) {
		if (phil->last_meal + phil->args->time_to_die < get_time_in_ms()) {
			if (phil->args->goal == DieGoal)
				phil->args->goal_data--;
			phil->is_dead = 1;
			break ;
		}
		usleep(STARVE_WORKER_SLEEP_MS * 1000);
	}
	if (phil->is_dead) {
		if (!log_state(Dying, phil->id))
			phil->args->crash_exit = 1;
	}
}

void		start_starve_worker(t_phil *phil) {
	if (pthread_create(&(phil->starve_worker), NULL, starve_checker, (void *)phil) != 0)
		phil->args->crash_exit = 1;
}
