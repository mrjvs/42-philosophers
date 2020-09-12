#include "boot.h"

int		main(int argc, char *argv[]) {
	t_phil_args	args;

	parse_args(argc, argv, &args);
	boot_sequence(&args);
	return 0;
}
