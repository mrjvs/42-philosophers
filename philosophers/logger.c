#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include "philosopher.h"
#include "utils.h"

long long	get_time_in_ms(void) {
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

static void	do_logging(int id, char *suffix) {
	char	*out;

	out = phil_make_log(get_time_in_ms(), id, suffix);
	if (out == NULL)
		return ;
	write(0, out, phil_strlen(out));
	free(out);
}

void		log_state(enum e_philstate state, int id) {
	char	*text;

	if (state == Thinking)
		text = "is thinking\n";
	else if (state == Eating)
		text = "is eating\n";
	else if (state == Sleeping)
		text = "is sleeping\n";
	else if (state == Taking)
		text = "has taken a fork\n";
	else if (state == Dying)
		text = "died\n";
	else
		text = "has been behaving unexpectedly\n";
	do_logging(id, text);
}
