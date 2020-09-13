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

int			start_philosophers(t_phil_args *args) {
	int 			i;
	t_thread_args	*tid;

	tid = (t_thread_args *)malloc(args->amount * sizeof(t_thread_args));
	if (tid == NULL)
		return (0);
	i = 0;
	while (i < args->amount) {
		tid[i].id = i;
		tid[i].args = args;
		if (pthread_create(&(tid[i].tid), NULL, create_philosopher, (void *__restrict)(&tid[i])) != 0)
			args->crash_exit = 1;
		i++;
	}
	join_philosophers(args, tid);
	return (1);
}