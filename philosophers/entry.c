#include <stddef.h>
#include "boot.h"
#include "philosopher.h"

static t_phil	make_phil_state(t_phil_args *args, int id) {
	t_phil	phil;

	phil.is_dead = 0;
	phil.last_meal = get_time_in_ms();
	phil.id = id;
	phil.args = args;
	phil.eat_countdown = args->eat_goal_amount;
	phil.starve_worker = -1;
	return (phil);
}

void			*create_philosopher(void *arg) {
	int		activity;
	t_phil	phil;

	phil = make_phil_state(((t_thread_args *)arg)->args, ((t_thread_args *)arg)->id);
	start_starve_worker(&phil);
	activity = 0;
	while (should_run(&phil)) {
		if (!do_action(&phil, activity))
			trigger_crash(&phil);
		activity++;
		if (activity > 2)
			activity = 0;
	}
	if (phil.starve_worker != -1)
		pthread_join(phil.starve_worker, NULL);
}
