/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 18:49:24 by wkerdad           #+#    #+#             */
/*   Updated: 2026/07/10 18:54:57 by wkerdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"codexion.h"

void *safe_malloc(size_t size)
{
    void *holder;
    
    holder = malloc(size);
    if (holder == NULL)
    {
        printf("malloc ERROR");
        exit(0);
    }
    return (holder);
}