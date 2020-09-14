#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "philosopher.h"
#include "boot.h"

static void	*crash_worker(void *arg) {
	t_phil_args	*args;

	args = (t_phil_args *)arg;
	sem_wait(args->phil_crash_lock);
	args->crash_exit = 1;
	sem_post(args->phil_died_lock);
}

static void	*eat_worker(void *arg) {
	int			i;
	t_phil_args	*args;

	args = (t_phil_args *)arg;
	i = 0;
	while (i < args->amount) {
		sem_wait(args->phil_eat_lock);
		i++;
	}
	sem_post(args->phil_died_lock);
}

static int	start_workers(t_phil_args *args) {
	pthread_t	tid;

	if (pthread_create(&tid, NULL, crash_worker, (void *)args) != 0)
		return (0);
	pthread_detach(tid);
	if (pthread_create(&tid, NULL, eat_worker, (void *)args) != 0)
		return (0);
	pthread_detach(tid);
	return (1);
}

int			start_philosophers(t_phil_args *args) {
	int 			i;
	pid_t			temp;
	t_thread_args	*tid;

	if (!start_workers(args))
		return (0);
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
	return (1);
}