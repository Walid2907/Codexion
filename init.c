/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 17:05:59 by wkerdad           #+#    #+#             */
/*   Updated: 2026/07/08 18:07:06 by wkerdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"codexion.h"


void    init(t_args *data)
{
    int i;

    pthread_mutex_init(&data->print_mutex, NULL);
    data->dongles = malloc(sizeof(t_dongle) * data->number_of_coders);
    if (!data->dongles)
        return;
    i = 0;
    while (i < data->number_of_coders)
    {
        data->dongles[i].dongle_id = i + 1;
        data->dongles[i].status = 0;
        pthread_mutex_init(&data->dongles[i].dongle, NULL);
        pthread_cond_init(&data->dongles[i].cond, NULL);
        i++;
    }
    // Next step: create coder threads, monitor thread, etc.
    // For now, init is just a setup entry point
}