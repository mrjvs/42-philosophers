#include "state.h"

t_ftbool	has_phil_died_state = false;

t_ftbool	has_phil_died(void) {
	return has_phil_died_state;
}

void	set_phil_died(t_ftbool state) {
	has_phil_died_state = state;
}
