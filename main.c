/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 23:58:02 by wkerdad           #+#    #+#             */
/*   Updated: 2026/07/12 15:53:20 by wkerdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


int	main(int argc, char **argv)
{
    // data is a holder of all the data in my program
	t_data *data = safe_malloc(sizeof(t_data));

    // strat by parsing and storing on the data->args
	if (argc != 9)
	{
		printf("Usage: ./codexion number_of_coders time_to_burnout time_to_compile "
			"time_to_debug time_to_refactor number_of_compiles_required "
			"dongle_cooldown scheduler\n");
		return (0);
	}
	data->args = parser(argc, argv);
    if (data->args == NULL)
    {
        free(data);
        return (1);
    }

    // arguments parsed and ready in data->args
    // now we need to initialize the other data
    if (init(data) == FAILED)
    {
        // clean function
        return (0);
    }

    
	return (0);
}
