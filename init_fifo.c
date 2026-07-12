/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fifo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 17:05:59 by wkerdad           #+#    #+#             */
/*   Updated: 2026/07/12 17:51:51 by wkerdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"codexion.h"

static void coders_hand_init(t_data *data, int position)
{
    // initialize the hands of each coder
    // ODD coders
    data->coders[position].left_hand = &data->dongles[position];
    data->coders[position].right_hand = &data->dongles[(position + 1) % data->args->number_of_coders];
    // EVEN coders
    if (data->coders[position].coder_id % 2 == 0)
    {
        data->coders[position].right_hand = &data->dongles[position];
        data->coders[position].left_hand = &data->dongles[(position + 1) % data->args->number_of_coders];
    }
}

static void coder_init(t_data *data)
{
    int i;
    
    i = 0;
    while(i < data->args->number_of_coders)
    {
        data->coders[i].coder_id = i + 1;
        data->coders[i].compile_counter = 0;
        data->coders[i].is_done = false;
        data->coders[i].status = WAITING;
        coders_hand_init(data, i);
        printf("-%d:", data->coders[i].coder_id);
        printf("%d,", data->coders[i].left_hand->dongle_id);
        printf(" %d\n", data->coders[i].right_hand->dongle_id);
        i++;
    }
   
}


void    init(t_data *data)
{
    int i;
    
    i = 0;
    data->end_sum = false;
    data->all_thread_ready = false;
    data->coders = safe_malloc(sizeof(t_coder) * data->args->number_of_coders);
    data->dongles = safe_malloc(sizeof(t_dongle) * data->args->number_of_coders);
    while(i < data->args->number_of_coders)
    {
        if (safe_mutex(INIT, &data->dongles[i].dongle) == FAILED)
            return (FAILED);
        data->dongles[i].dongle_id = i + 1;
        data->dongles[i].status = READY;
        i++;
    }
    coder_init(data);
    
}