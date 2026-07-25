/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 02:04:26 by wkerdad           #+#    #+#             */
/*   Updated: 2026/07/25 15:08:27 by wkerdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

// function that waits for the threads to be created safely
// and quit when needed
void	wait_all_thread(t_data *data)
{
	while (get_bool(&data->all_th_rd_mutex, &data->all_th_rd) != true)
		usleep(50);
}

void	dongle_init_helper(t_data *data, int *i)
{
	while (*(--i) >= 0)
	{
		safe_mutex(DESTROY, &data->dongles_arr[*i].dongle_mutex);
		safe_mutex(DESTROY, &data->dongles_arr[*i].available_at_mutex);
		safe_mutex(DESTROY, &data->dongles_arr[*i].queue_mutex);
		pthread_cond_destroy(&data->dongles_arr[*i].queue_cond);
	}
	safe_mutex(DESTROY, &data->data_mutex);
	safe_mutex(DESTROY, &data->print_msg_mutex);
	safe_mutex(DESTROY, &data->all_th_rd_mutex);
	safe_mutex(DESTROY, &data->simulation_done_mutex);
}

void	helper_helper_2(t_coder *coder, t_dongle *dongle, bool *lk)
{
	t_ull	available;

	dongle->queue = coder->wait_node.next;
	safe_mutex(UNLOCK, &dongle->queue_mutex);
	safe_mutex(LOCK, &dongle->dongle_mutex);
	while (!get_bool(&coder->data->simulation_done_mutex,
			&coder->data->simulation_done))
	{
		available = get_long(&dongle->available_at_mutex,
				&dongle->available_at);
		if (get_time() >= available)
			break ;
		usleep(500);
	}
	if (get_bool(&coder->data->simulation_done_mutex,
			&coder->data->simulation_done))
	{
		safe_mutex(UNLOCK, &dongle->dongle_mutex);
		*lk = false;
	}
}
