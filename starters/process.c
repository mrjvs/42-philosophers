#include <pthread.h>
#include <stdlib.h>
#include <signal.h>
#include "philosopher.h"
#include "boot.h"

static void	crash_worker(t_phil_args *args) {
	sem_wait(args->phil_crash_lock);
	args->crash_exit = 1;
	sem_post(args->phil_died_lock);
}

static void	eat_worker(t_phil_args *args) {
	int	i;

	i = 0;
	while (i < args->amount) {
		// sem_wait(philosopher_eat_lock_IDHERE);
		i++;
	}
	sem_post(args->phil_died_lock);
}

static void	start_workers() {
	// start crash worker
	// start eat worker
}

int			start_philosophers(t_phil_args *args) {
	int 			i;
	pid_t			temp;
	t_thread_args	*tid;

	tid = (t_thread_args *)malloc(args->amount * sizeof(t_thread_args));
	if (tid == NULL)
		return (0);
	i = 0;
	while (i < args->amount) {
		tid[i].id = i;
		tid[i].args = args;
		temp = fork(); // ! tid < 0
		if (temp == 0) {
			create_philosopher((void *)&(tid[i]));
			exit(0);
		}
		tid[i].tid = temp;
		i++;
	}
	sem_wait(args->phil_died_lock);
	i = 0;
	while (i < args->amount) {
		kill(tid[i].tid, SIGKILL);
		i++;
	}
	free(tid);
	if (args->)
	return (1);
}