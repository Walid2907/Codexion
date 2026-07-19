/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 02:05:23 by wkerdad           #+#    #+#             */
/*   Updated: 2026/07/15 02:33:19 by wkerdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

// usleep but in ms with some checks
void	ft_usleep(ull_t sleep_time, t_data *data)
{
	ull_t	start;

	start = get_time();
	while ((get_time() - start) < sleep_time)
    {
        if (get_bool(&data->simulation_done_mutex, &data->simulation_done) == true)
            break;
		usleep(500);
    }
}

ull_t	get_time()
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * (ull_t)1000) + (tv.tv_usec / 1000));
}
