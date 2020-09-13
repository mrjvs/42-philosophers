#include <stddef.h>
#include <pthread.h>
#include <unistd.h>
#include "philosopher.h"

static void	*starve_checker(void *arg) {
	t_phil	*phil;

	phil = (t_phil *)arg;
	while (should_run(phil)) {
		if (phil->last_meal + phil->args->time_to_die < get_time_in_ms()) {
			trigger_has_died(phil);
			phil->is_dead = 1;
			break ;
		}
		usleep(STARVE_WORKER_SLEEP_MS * 1000);
	}
	if (phil->is_dead) {
		if (!log_state(Dying, phil->id))
			trigger_crash(phil);
	}
}

void		start_starve_worker(t_phil *phil) {
	if (pthread_create(&(phil->starve_worker), NULL, starve_checker, (void *)phil) != 0)
		trigger_crash(phil);
}
