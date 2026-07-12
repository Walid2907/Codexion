/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 18:37:47 by wkerdad           #+#    #+#             */
/*   Updated: 2026/07/12 20:00:23 by wkerdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void    wait_threads(t_data *data)
{
    while(!get_bool(&data->data_mutex, &data->all_thread_ready))
        usleep(10);
}