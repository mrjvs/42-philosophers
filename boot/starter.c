#include <pthread.h>
#include <stdlib.h>
#include "philosopher.h"
#include "boot.h"

static void	join_philosophers(t_phil_args *args, t_thread_args *tid) {
	int	i;

	i = 0;
	while (i < args->amount) {
		pthread_join(tid[i].tid, NULL);
		i++;
	}
	free(tid);
}

static void	start_philosophers(t_phil_args *args) {
	int 			i;
	t_thread_args	*tid;

	tid = (t_thread_args *)malloc(args->amount * sizeof(t_thread_args));
	i = 0;
	while (i < args->amount) {
		tid[i].id = i;
		tid[i].args = args;
		pthread_create(&(tid[i].tid), NULL, create_philosopher, (void *__restrict)(&tid[i]));
		i++;
	}
	join_philosophers(args, tid);
}

void		boot_sequence(t_phil_args *args) {
	start_philosophers(args);
}
