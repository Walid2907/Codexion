/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 06:04:53 by wkerdad           #+#    #+#             */
/*   Updated: 2026/07/18 22:59:31 by wkerdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


static void    release_dongle(t_coder *coder, t_dongle *dongle)
{
    ull_t value;

    value = get_time() + coder->data->args->dongle_cooldown;
    set_long(&dongle->available_at_mutex, &dongle->available_at, value);
    safe_mutex(UNLOCK, &dongle->dongle_mutex);
    safe_mutex(LOCK, &dongle->queue_mutex);
    pthread_cond_broadcast(&dongle->queue_cond);
    safe_mutex(UNLOCK, &dongle->queue_mutex);
}

static bool    take_dongles(t_coder *coder)
{
    bool lk;

    lk = true;
    request_dongle(coder, coder->right_hand, &lk);
    if (get_bool(&coder->data->simulation_done_mutex, &coder->data->simulation_done))
    {
        if (lk == true)
            release_dongle(coder, coder->right_hand);
        return (FAILED);
    }
    print_msg(coder, TAKE_FIRST_DG);
    if (coder->right_hand == coder->left_hand)
    {
        while (!get_bool(&coder->data->simulation_done_mutex,
                &coder->data->simulation_done))
            usleep(50);
        release_dongle(coder, coder->right_hand);
        return (FAILED);
    }
    request_dongle(coder, coder->left_hand, &lk);
    if (get_bool(&coder->data->simulation_done_mutex, &coder->data->simulation_done))
    {
        if (lk == true)
        {
            release_dongle(coder, coder->right_hand);
            release_dongle(coder, coder->left_hand);
        }
        else
            release_dongle(coder, coder->right_hand);
        return (FAILED);
    }
    print_msg(coder, TAKE_SECOND_DG);
    return (SUCCESS);
}

int compile(t_coder *coder)
{
    // take dongles
    if (take_dongles(coder) == FAILED)
        return (FAILED);
    // start the compile
    set_long(&coder->last_compile_mutex, &coder->last_compile, get_time());
    increment_int(&coder->compile_counter_mutex, &coder->compile_counter);
    print_msg(coder, COMPILE);
    // compile
    ft_usleep(coder->data->args->time_to_compile, coder->data);
    if (get_int(&coder->compile_counter_mutex, &coder->compile_counter) >= coder->data->args->number_of_compiles_required)
        set_bool(&coder->is_done_mutex, &coder->is_done, true);
    // release dongles
    release_dongle(coder, coder->right_hand);
    if (coder->right_hand != coder->left_hand)
        release_dongle(coder, coder->left_hand);
    return (SUCCESS);
}