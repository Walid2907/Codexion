/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 16:00:00 by wkerdad           #+#    #+#             */
/*   Updated: 2026/07/18 23:35:44 by wkerdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void request_dongle(t_coder *coder, t_dongle *dongle, bool *lk)
{
    t_dongle_wait **walk;

    safe_mutex(LOCK, &dongle->queue_mutex);
    coder->wait_node.coder_id = coder->coder_id;
    coder->wait_node.next = NULL;
    *lk = true;
    walk = &dongle->queue;
    while (*walk)
        walk = &(*walk)->next;
    *walk = &coder->wait_node;
    while (1)
    {
        if (get_bool(&coder->data->simulation_done_mutex, &coder->data->simulation_done))
            break;
        if (dongle->queue == &coder->wait_node)
        {
            ull_t available;
            
            if (coder->data->args->scheduler == "fifo")
                available = get_long(&dongle->available_at_mutex, &dongle->available_at);
            else
                available = coder->last_compile + coder->data->args->time_to_burnout;
            if (get_time() >= available)
                break;
            else
            {
                struct timeval tv;
                struct timespec ts;
                ull_t wait_ms;

                gettimeofday(&tv, NULL);
                wait_ms = available - get_time();
                ts.tv_sec = tv.tv_sec + wait_ms / 1000;
                ts.tv_nsec = (tv.tv_usec + (wait_ms % 1000) * 1000) * 1000;
                if (ts.tv_nsec >= 1000000000)
                {
                    ts.tv_sec++;
                    ts.tv_nsec -= 1000000000;
                }
                pthread_cond_timedwait(&dongle->queue_cond,
                    &dongle->queue_mutex, &ts);
            }
        }
        else
            pthread_cond_wait(&dongle->queue_cond, &dongle->queue_mutex);
    }
    if (get_bool(&coder->data->simulation_done_mutex, &coder->data->simulation_done))
    {
        if (dongle->queue == &coder->wait_node)
            dongle->queue = coder->wait_node.next;
        else
        {
            t_dongle_wait *prev;

            prev = dongle->queue;
            while (prev && prev->next != &coder->wait_node)
                prev = prev->next;
            if (prev)
                prev->next = coder->wait_node.next;
        }
        safe_mutex(UNLOCK, &dongle->queue_mutex);
        *lk = false;
    }
    else
    {
        dongle->queue = coder->wait_node.next;
        safe_mutex(UNLOCK, &dongle->queue_mutex);
        safe_mutex(LOCK, &dongle->dongle_mutex);
    }
}
