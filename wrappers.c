/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 21:44:58 by wkerdad           #+#    #+#             */
/*   Updated: 2026/07/18 16:31:03 by wkerdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


/*
a wrapper for malloc simple to print that malloc is the one that
failed so i can quit directly
*/
void    *safe_malloc(size_t size)
{
    void    *holder;

    holder = malloc(size);
    if (holder == NULL)
    {
        printf("ERROR: Malloc failed\n");
        return (NULL);
    }
    return (holder);
}

int safe_thread(t_thread_op op, pthread_t *thread, void *(*routine)(void *), void *arg)
{
    int ret;

    if (op == CREATE)
        ret = pthread_create(thread, NULL, routine, arg);
    else if (op == JOIN)
        ret = pthread_join(*thread, NULL);
    else
        return (FAILED);

    if (ret != 0)
    {
        printf("ERROR: Thread failed\n");
        return (FAILED);
    }
    return (SUCCESS);
}

int safe_mutex(t_mutex_op op, pthread_mutex_t *mutex)
{
    int ret;

    if (op == INIT)
        ret = pthread_mutex_init(mutex, NULL);
    else if (op == DESTROY)
        ret = pthread_mutex_destroy(mutex);
    else
        return (FAILED);
    if (ret != 0)
    {
        printf("ERROR: Mutex failed\n %d", op);
        return (FAILED);
    }
    return (SUCCESS);
}
