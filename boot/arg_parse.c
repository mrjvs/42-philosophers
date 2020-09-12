#include "boot.h"

void	parse_args(int argc, char *argv[], t_phil_args *args) {
	args->amount = 2;
	args->time_to_eat = 5000;
	args->time_to_sleep = 1000;
	args->time_to_die = 6500;
	args->eat_goal_amount = 0;

	// die goal
	// args->goal = DieGoal;
	// args->goal_data = AMOUNT_DEAD_UNTIL_STOP;

	// eat goal
	args->goal = EatGoal;
	args->goal_data = args->amount;
	args->eat_goal_amount = 6;
}
