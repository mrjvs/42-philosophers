#include <unistd.h>
#include "philosopher.h"
#include "state.h"

// TODO dynamic sleeping
// TODO block until forks
void	do_action(int id, int activity) {
	long	sleep_time;

	if (activity == Thinking) {
		sleep_time = 1000;
		if (id == 0) {
			set_phil_died(true);
			log_state(Dying, id);
			return ;
		}
	}
	else if (activity == Sleeping)
		sleep_time = 1000;
	else if (activity == Eating)
		sleep_time = 1000;
	log_state(activity, id);
	usleep(1000 * sleep_time);
}
