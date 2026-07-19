/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 14:01:13 by wkerdad           #+#    #+#             */
/*   Updated: 2026/07/18 23:11:57 by wkerdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


static void wait_all_thread(t_data *data)
{
    while (get_bool(&data->all_th_rd_mutex, &data->all_th_rd) != true)
        usleep(50);
}

static void    *routine(void *arg)
{
    t_coder *coder;
    
    coder = (t_coder *)arg;
    // we should wait for all the threads
    wait_all_thread(coder->data);
    // start the cycle
    while (get_bool(&coder->data->simulation_done_mutex, &coder->data->simulation_done) == false)
    {
        if (get_bool(&coder->is_done_mutex, &coder->is_done) == true)
            break;
        // compile
        if (compile(coder) == FAILED)
            break;
        // debug
        print_msg(coder, DEBUGE);
        ft_usleep(coder->data->args->time_to_debug, coder->data);
        // refactor
        print_msg(coder, REFACTOR);
        ft_usleep(coder->data->args->time_to_refactor, coder->data);
    }
    return (NULL);
}

static void *burnout_monitor(void *arg)
{
    t_data *data = (t_data *)arg;
    int i;
    int all_done;

    wait_all_thread(data);
    while (1)
    {
        i = 0;
        all_done = 1;
        while (i < data->args->number_of_coders)
        {
            if (get_bool(&data->coders_arr[i].is_done_mutex,
                &data->coders_arr[i].is_done) == false)
            {
                all_done = 0;
                if (get_time() - get_long(&data->coders_arr[i].last_compile_mutex,
                    &data->coders_arr[i].last_compile)
                    > (ull_t)data->args->time_to_burnout)
                {
                    print_msg(&data->coders_arr[i], BURNED_OUT);
                    set_bool(&data->simulation_done_mutex,
                        &data->simulation_done, true);
                    return (NULL);
                }
            }
            i++;
        }
        if (all_done)
        {
            set_bool(&data->simulation_done_mutex,
                &data->simulation_done, true);
            return (NULL);
        }
        usleep(500);
    }
    return (NULL);
}

int sim_start(t_data *data)
{
    int i;
    pthread_t monitor;

    i = 0;
    while (i < data->args->number_of_coders)
    {
        if (safe_thread(CREATE, &data->coders_arr[i].th, routine, &data->coders_arr[i]) == FAILED)
        {
            data->simulation_done = true;
            while (--i >= 0)
                safe_thread(JOIN, &data->coders_arr[i].th, NULL, NULL);
            return (FAILED);
        }
        i++;
    }
    // all threads are done start the simulation
    safe_thread(CREATE, &monitor, burnout_monitor, data);
    safe_mutex(LOCK, &data->data_mutex);
    data->simulation_start = get_time();
    safe_mutex(UNLOCK, &data->data_mutex);
    i = 0;
    while (i < data->args->number_of_coders)
    {
        set_long(&data->coders_arr[i].last_compile_mutex,
            &data->coders_arr[i].last_compile, data->simulation_start);
        i++;
    }
    set_bool(&data->all_th_rd_mutex, &data->all_th_rd, true);

    i = 0;
    while (i < data->args->number_of_coders)
    {
        safe_thread(JOIN, &data->coders_arr[i].th, NULL, NULL);
        i++;
    }
    safe_thread(JOIN, &monitor, NULL, NULL);
    return (SUCCESS);
}
