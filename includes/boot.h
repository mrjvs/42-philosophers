#ifndef BOOT_H
# define BOOT_H

# define AMOUNT_DEAD_UNTIL_STOP 1
# define SEM_DIE_LOCK "philosophersDieLock"
# define SEM_EAT_LOCK "philosophersEatLock"
# define SEM_CRASH_LOCK "philosophersCrashLock"


# define COMPILE_PHIL_THREADS

# ifdef COMPILE_COM_SHAREDMEM

typedef struct	s_phil_args {
	int 			amount;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_goal_amount;
	int				eat_goal_counter;
	int				has_died;
	int				crash_exit;
}				t_phil_args;

# else

#  include <semaphore.h>

typedef struct	s_phil_args {
	int 			amount;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_goal_amount;
	int				crash_exit;
	sem_t			*phil_died_lock;
	sem_t			*phil_eat_lock;
	sem_t			*phil_crash_lock;
}				t_phil_args;

# endif

# ifdef COMPILE_PHIL_THREADS

#  include <pthread.h>
typedef struct	s_thread_args
{
	t_phil_args	*args;
	int			id;
	pthread_t	tid;
}				t_thread_args;

# else

#  include <sys/types.h>
#  include <sys/wait.h>
typedef struct	s_thread_args
{
	t_phil_args	*args;
	int			id;
	pid_t		tid;
}				t_thread_args;

# endif

int		parse_args(int argc, char *argv[], t_phil_args *args);
int		boot_sequence(t_phil_args *args);
int		start_philosophers(t_phil_args *args);
void	init_args(t_phil_args *args);

#endif
