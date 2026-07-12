/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters_getters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 17:53:21 by wkerdad           #+#    #+#             */
/*   Updated: 2026/07/12 17:55:15 by wkerdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include"codexion.h"


void    get_bool(pthread_mutex_t *mx, bool *to_set, bool value)
{
    safe_mutex(LOCK, mx);
    *to_set = value;
    safe_mutex(UNLOCK, mx);
}