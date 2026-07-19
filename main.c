/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 21:13:46 by wkerdad           #+#    #+#             */
/*   Updated: 2026/07/15 15:27:20 by wkerdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


// the entry point
int main(int argc, char **argv)
{
    t_data *data;

	if (argc != 9)
	{
		printf("Usage: ./codexion number_of_coders time_to_burnout time_to_compile "
			"time_to_debug time_to_refactor number_of_compiles_required "
			"dongle_cooldown scheduler\n");
		return (0);
	}
    data = safe_malloc(sizeof(t_data));
    if (data == NULL)
        return (FAILED);
    data->args = parser(argc, argv);
    if (data->args == NULL)
    {
        free(data);
        return (FAILED);
    }
    if (data_init(data) == FAILED)
        return (cleanup(data, 1));

    if (sim_start(data))
        return (cleanup(data, 3));
    return (0);

}
