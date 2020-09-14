#include <unistd.h>
#include "boot.h"

int		main(int argc, char *argv[]) {
	t_phil_args	args;

	if (!parse_args(argc, argv, &args)) {
		if (args.crash_exit == 1)
			write(1, "An error occured, whoops\n", 25);
		return (1);
	}
	if (!boot_sequence(&args)) {
		write(1, "An error occured, whoops\n", 25);
		return (1);
	}
	return (0);
}
