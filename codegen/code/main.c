/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mrjvs <mrjvs@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/14 16:00:49 by mrjvs         #+#    #+#                 */
/*   Updated: 2020/09/15 16:29:04 by mrjvs         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philosophers.h"

static int	boot_sequence(t_phil_args *args)
{
	int	status;

	status = start_philosophers(args);
	destroy_locks(args);
	destroy_forks(args);
	if (!status || args->crash_exit)
		return (0);
	return (1);
}

int			main(int argc, char *argv[])
{
	t_phil_args	args;

	if (!parse_args(argc, argv, &args))
	{
		if (args.crash_exit == 1)
			write(1, "An error occured, whoops\n", 25);
		return (1);
	}
	if (!boot_sequence(&args))
	{
		write(1, "An error occured, whoops\n", 25);
		return (1);
	}
	return (0);
}
