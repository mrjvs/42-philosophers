#include <pthread.h>
#include <stdlib.h>
#include "philosopher.h"

static void	start_philosophers(int philosopher_amount) {
	int 		i;
	pthread_t	*tid;

	tid = (pthread_t *)malloc(philosopher_amount * sizeof(pthread_t));
	i = 0;
	while (i < philosopher_amount) {
		pthread_create(&tid[i], NULL, create_philosopher, (void *__restrict)i);
		i++;
	}
	i = 0;
	while (i < philosopher_amount) {
		pthread_join(tid[i], NULL);
		i++;
	}
	free(tid);
}

void		boot_sequence(int philosopher_amount) {
	start_philosophers(philosopher_amount);
}
