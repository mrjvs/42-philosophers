#ifndef BOOT_H
# define BOOT_H

# include <pthread.h>

# define AMOUNT_DEAD_UNTIL_STOP 1

enum e_goals {
	EatGoal,
	DieGoal
};

/*
** goal_data: Counter, if it reaches zero. simulation stops
*/
typedef struct	s_phil_args {
	int 			amount;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	enum e_goals	goal;
	int				eat_goal_amount;
	int				goal_data;
}				t_phil_args;

typedef struct	s_thread_args
{
	t_phil_args	*args;
	int			id;
	pthread_t	tid;
}				t_thread_args;


void	parse_args(int argc, char *argv[], t_phil_args *args);
void	boot_sequence(t_phil_args *args);

#endif
