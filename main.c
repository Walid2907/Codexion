/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 23:58:02 by wkerdad           #+#    #+#             */
/*   Updated: 2026/07/08 18:09:32 by wkerdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


int	main(int argc, char **argv)
{
	t_args	*data;

	if (argc != 9)
	{
		printf("Usage: ./codexion number_of_coders time_to_burnout time_to_compile "
			"time_to_debug time_to_refactor number_of_compiles_required "
			"dongle_cooldown scheduler\n");
		return (0);
	}
	check_args(argv);
	data = parser(argc, argv);
	if (!data)
	{
		printf("ERROR: Memory allocation failed\n");
		return (0);
	}
    // arguments parsed and ready in data
	init(data);
    free(data->dongles);
    pthread_mutex_destroy(&data->print_mutex);
    free(data);
	return (0);
}
