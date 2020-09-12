#include <unistd.h>
#include "philosopher.h"

static int	do_eat(t_phil *phil) {
	// TODO gather forks
	phil->last_meal = get_time_in_ms();
	if (phil->eat_countdown > 0) {
		phil->eat_countdown--;
		if (phil->eat_countdown == 0)
			phil->args->goal_data--;
	}
	return (1);
}

void		do_action(t_phil *phil, int activity) {
	int	sleep_time;

	if (activity == Thinking)
		sleep_time = 0; // TODO wtf do I do here?
	else if (activity == Sleeping)
		sleep_time = phil->args->time_to_sleep;
	else if (activity == Eating) {
		sleep_time = phil->args->time_to_eat;
		if (!do_eat(phil))
			return ;
	}
	log_state(activity, phil->id);
	usleep(1000 * sleep_time);
}
