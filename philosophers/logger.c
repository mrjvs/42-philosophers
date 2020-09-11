#include <sys/time.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "philosopher.h"

static long long	get_time_in_ms(void) {
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec + (time.tv_usec / 1000));
}

// TODO remove printf statement AND use own strlen
static void	do_logging(int id, char *suffix) {
	char			*out;

	asprintf(&out, "%lld %d %s\n", get_time_in_ms(), id, suffix);
	write(0, out, strlen(out));
	free(out);
}

void	log_state(enum e_philstate state, int id) {
	char	*text;

	if (state == Thinking)
		text = "is thinking";
	else if (state == Eating)
		text = "is eating";
	else if (state == Sleeping)
		text = "is sleeping";
	else if (state == Taking)
		text = "has taken a fork";
	else if (state == Dying)
		text = "died";
	else
		text = "has been behaving unexpectedly";
	do_logging(id, text);
}
