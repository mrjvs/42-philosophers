#include <unistd.h>
#include "philosopher.h"

static int	do_eat(t_phil *phil) {
	// TODO gather forks
	phil->last_meal = get_time_in_ms();
	if (phil->eat_countdown > 0) {
		phil->eat_countdown--;
		if (phil->eat_countdown == 0)
			finish_eat_goal(phil);
	}
	return (1);
}

int			do_action(t_phil *phil, int activity) {
	int	sleep_time;

	if (activity == Thinking)
		sleep_time = 0; // TODO wtf do I do here?
	else if (activity == Sleeping)
		sleep_time = phil->args->time_to_sleep;
	else if (activity == Eating) {
		sleep_time = phil->args->time_to_eat;
		if (!do_eat(phil))
			return (0);
	}
	if (!log_state(activity, phil->id))
		return (0);
	usleep(1000 * sleep_time);
	return (1);
}
