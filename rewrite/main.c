/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mrjvs <mrjvs@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 12:38:46 by mrjvs         #+#    #+#                 */
/*   Updated: 2020/09/16 16:40:56 by mrjvs         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char *argv[])
{
	t_phil_global	globals;

	(void)argc;
	(void)argv;
	if (!init_globals(&globals))
		return (1);
	if (!seat_philosophers(&globals))
		return (1);
	return (0);
}
