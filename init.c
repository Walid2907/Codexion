/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 17:05:59 by wkerdad           #+#    #+#             */
/*   Updated: 2026/07/11 20:50:27 by wkerdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"codexion.h"

static void coders_hand_init(t_data *data, int position)
{
    // initialize the hands of each coder
    data->coders[position].right_hand = &data->dongles[position];
    data->coders[position].left_hand = &data->dongles[(position + 1) % data->args->number_of_coders];

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
    data->coders = safe_malloc(sizeof(t_coder) * data->args->number_of_coders);
    data->dongles = safe_malloc(sizeof(t_dongle) * data->args->number_of_coders);
    while(i < data->args->number_of_coders)
    {
        safe_mutex(INIT, &data->dongles[i].dongle);
        data->dongles[i].dongle_id = i + 1;
        i++;
    }
    coder_init(data);
    
}