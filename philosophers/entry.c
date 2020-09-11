#include <string.h>
#include <unistd.h>
#include "state.h"

void	*create_philosopher(void *arg) {
	int id;
	int	activity;

	id = (int)arg;
	activity = 0;
	while (!has_phil_died()) {
		do_action(id, activity);
		activity++;
		if (activity > 2)
			activity = 0;
	}
}
