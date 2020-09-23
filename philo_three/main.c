/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mrjvs <mrjvs@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 12:38:46 by mrjvs         #+#    #+#                 */
/*   Updated: 2020/09/23 13:26:44 by mrjvs         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philosophers.h"

int	main(int argc, char *argv[])
{
	t_phil_global	globals;

	if (!parse_args(argc, argv, &globals))
	{
		write(STDERR_FILENO, "Whoops, Invalid arguments!\n", 27);
		return (1);
	}
	if (!init_globals(&globals))
	{
		write(STDERR_FILENO, "Whoops, Something went wrong!\n", 30);
		return (1);
	}
	if (!seat_philosophers(&globals))
	{
		write(STDERR_FILENO, "Whoops, Something went wrong!\n", 30);
		clear_globals(&globals);
		return (1);
	}
	return (0);
}
