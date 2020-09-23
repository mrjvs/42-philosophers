/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mrjvs <mrjvs@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/17 17:45:36 by mrjvs         #+#    #+#                 */
/*   Updated: 2020/09/23 14:21:13 by mrjvs         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include "philosophers.h"

static long	phil_atoi(char *str)
{
	int		i;
	long	out;

	out = 0;
	i = 0;
	if (str[0] == '\0')
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		out *= 10;
		out += str[i] - '0';
		if (out > INT_MAX)
			return (-1);
		i++;
	}
	return (out);
}

ssize_t		phil_putnbr(unsigned long long n)
{
	unsigned long long	i;
	int					charcount;
	char				arr[21];

	i = n;
	charcount = 0;
	while (i > 9)
	{
		charcount++;
		i = i / 10;
	}
	i = charcount + 1;
	arr[charcount + 1] = 0;
	while (n > 9)
	{
		arr[charcount] = '0' + (n % 10);
		n = n / 10;
		charcount--;
	}
	arr[charcount] = '0' + (n % 10);
	return (write(STDOUT_FILENO, arr, i));
}

size_t		phil_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int			parse_args(int argc, char *argv[], t_phil_global *globals)
{
	if (argc < 5 || argc > 6)
		return (0);
	globals->amount = phil_atoi(argv[1]);
	globals->time_to_die = phil_atoi(argv[2]);
	globals->time_to_eat = phil_atoi(argv[3]);
	globals->time_to_sleep = phil_atoi(argv[4]);
	globals->eat_goal = argc == 6 ? phil_atoi(argv[5]) : -2;
	globals->crash_exit = 0;
	if (globals->amount == -1 ||
		globals->time_to_die == -1 ||
		globals->time_to_eat == -1 ||
		globals->time_to_sleep == -1 ||
		globals->eat_goal == -1)
		return (0);
	return (1);
}
