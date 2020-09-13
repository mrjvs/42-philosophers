#include "boot.h"

int			boot_sequence(t_phil_args *args) {
	int	status;

	status = start_philosophers(args);
	if (!status || args->crash_exit)
		return (0);
	return (1);
}
