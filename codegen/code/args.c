/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   args.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mrjvs <mrjvs@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 16:00:47 by mrjvs         #+#    #+#                 */
/*   Updated: 2020/09/15 16:28:45 by mrjvs         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philosophers.h"

static int	is_valid_int(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	if (i > INT_CHARLEN || (i == INT_CHARLEN && phil_atoi(str) > INT_MAXLEN))
		return (0);
	return (1);
}

static int	is_valid_int_arr(char *strs[], int n)
{
	while (n > 0)
	{
		n--;
		if (!is_valid_int(strs[n]))
			return (0);
	}
	return (1);
}

int			parse_args(int argc, char *argv[], t_phil_args *args)
{
	if (((argc < 5 || argc > 6) || !is_valid_int_arr(argv + 1, 4)) ||
		(argc == 6 && (!is_valid_int(argv[5]) || phil_atoi(argv[5]) == 0)))
	{
		write(2, "Invalid arguments\n", 19);
		return (0);
	}
	args->amount = phil_atoi(argv[1]);
	args->time_to_die = phil_atoi(argv[2]);
	args->time_to_eat = phil_atoi(argv[3]);
	args->time_to_sleep = phil_atoi(argv[4]);
	args->eat_goal_amount = 0;
	if (argc == 6)
		args->eat_goal_amount = phil_atoi(argv[5]);
	args->crash_exit = 0;
	if (!init_args(args) || !init_forks(args))
	{
		args->crash_exit = 1;
		return (0);
	}
	return (1);
}
