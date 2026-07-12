/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters_getters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 17:53:21 by wkerdad           #+#    #+#             */
/*   Updated: 2026/07/12 18:30:31 by wkerdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include"codexion.h"


int    set_bool(pthread_mutex_t *mx, bool *to_set, bool value)
{
    if(safe_mutex(LOCK, mx) == FAILED)
        return (FAILED);
    *to_set = value;
    if(safe_mutex(UNLOCK, mx) == FAILED)
        return (FAILED);
    return (SUCCESS);
}
bool    get_bool(pthread_mutex_t *mx, bool *value)
{
    bool res;
    
    safe_mutex(LOCK, mx);
    res = *value;
    safe_mutex(UNLOCK, mx);
    return (res);
}

int    set_int(pthread_mutex_t *mx, int *to_set, int value)
{
    if(safe_mutex(LOCK, mx) == FAILED)
        return (FAILED);
    *to_set = value;
    if(safe_mutex(UNLOCK, mx) == FAILED)
        return (FAILED);
    return (SUCCESS);
}

int    get_int(pthread_mutex_t *mx, int *value)
{
    int res;
    
    safe_mutex(LOCK, mx);
    res = *value;
    safe_mutex(UNLOCK, mx);
    return (res);
}

bool sim_finished(t_data *data)
{
    return(get_bool(&data->data_mutex, &data->end_sum));
}