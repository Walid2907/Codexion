/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 23:58:02 by wkerdad           #+#    #+#             */
/*   Updated: 2026/07/11 20:46:48 by wkerdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


int	main(int argc, char **argv)
{
    // data is a holder of all the data in my program
	t_data *data = malloc(sizeof(t_data));

    // strat by parsing and storing on the data->args
	if (argc != 9)
	{
		printf("Usage: ./codexion number_of_coders time_to_burnout time_to_compile "
			"time_to_debug time_to_refactor number_of_compiles_required "
			"dongle_cooldown scheduler\n");
		return (0);
	}
	data->args = parser(argc, argv);

    // arguments parsed and ready in data->args
    // now we need to initialize the other data
    init(data);

    
	return (0);
}
