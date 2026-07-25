/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 16:00:00 by wkerdad           #+#    #+#             */
/*   Updated: 2026/07/25 15:44:15 by wkerdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	helper_helper_1(t_dongle *dongle, t_ull available)
{
	t_ull			wait_ms;
	struct timeval	tv;
	struct timespec	ts;

	gettimeofday(&tv, NULL);
	if (available <= get_time())
		return ;
	wait_ms = available - get_time();
	ts.tv_sec = tv.tv_sec + wait_ms / 1000;
	ts.tv_nsec = (tv.tv_usec + (wait_ms % 1000) * 1000) * 1000;
	if (ts.tv_nsec >= 1000000000)
	{
		ts.tv_sec++;
		ts.tv_nsec -= 1000000000;
	}
	pthread_cond_timedwait(&dongle->queue_cond, &dongle->queue_mutex, &ts);
}

static void	helper_1(t_coder *coder, t_dongle *dongle)
{
	t_ull	available;

	while (1)
	{
		if (get_bool(&coder->data->simulation_done_mutex,
				&coder->data->simulation_done))
			break ;
		if (dongle->queue == &coder->wait_node)
		{
			available = get_long(&dongle->available_at_mutex,
					&dongle->available_at);
			if (get_time() >= available)
				break ;
			else
			{
				helper_helper_1(dongle, available);
			}
		}
		else
			pthread_cond_wait(&dongle->queue_cond, &dongle->queue_mutex);
	}
}

static void	helper_2(t_coder *coder, t_dongle *dongle, bool *lk)
{
	t_dongle_wait	*prev;

	if (get_bool(&coder->data->simulation_done_mutex,
			&coder->data->simulation_done))
	{
		if (dongle->queue == &coder->wait_node)
			dongle->queue = coder->wait_node.next;
		else
		{
			prev = dongle->queue;
			while (prev && prev->next != &coder->wait_node)
				prev = prev->next;
			if (prev)
				prev->next = coder->wait_node.next;
		}
		safe_mutex(UNLOCK, &dongle->queue_mutex);
		pthread_cond_broadcast(&dongle->queue_cond);
		*lk = false;
	}
	else
	{
		helper_helper_2(coder, dongle, lk);
	}
}

static void	helper_3(t_coder *coder, t_dongle *dongle)
{
	t_dongle_wait	**holder;

	// coder->wait_node.next = dongle->queue;
	// dongle->queue = &coder->wait_node;
	if (coder->data->args->scheduler == FIFO)
	{
        coder->wait_node.next = dongle->queue;
        dongle->queue = &coder->wait_node;
	}
	else
	{
		holder = &dongle->queue;
		while (*holder && (*holder)->deadline <= coder->wait_node.deadline)
			holder = &(*holder)->next;
		coder->wait_node.next = *holder;
		*holder = &coder->wait_node;
	}
}

void	request_dongle(t_coder *coder, t_dongle *dongle, bool *lk)
{
	safe_mutex(LOCK, &dongle->queue_mutex);
	coder->wait_node.coder_id = coder->coder_id;
	coder->wait_node.next = NULL;
	coder->wait_node.deadline = get_long(&coder->last_compile_mutex,
			&coder->last_compile) + coder->data->args->time_to_burnout;
	*lk = true;
	helper_3(coder, dongle);
	helper_1(coder, dongle);
	helper_2(coder, dongle, lk);
}
