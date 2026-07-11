/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkerdad <wkerdad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 18:49:24 by wkerdad           #+#    #+#             */
/*   Updated: 2026/07/11 20:27:25 by wkerdad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"codexion.h"


static void wrapp_mutex_error(int status, t_move move)
{
    if (0== status)
    return;
    if (EINVAL == status && (LOCK == move || UNLOCK == move || DESTROY == move))
        printf("The value specified by mutex is invalid.");
    else if (EINVAL == status && INIT == move)
        printf("The value specified by attr is invalid.");
    else if (EDEADLK == status)
        printf("A deadlock would occur if the thread blocked waiting for mutex.");
    else if (EPERM == status)
        printf("The current thread does not hold a lock on mutex.");
    else if (ENOMEM == status)
        printf("The process cannot allocate enough memory to create another mutex.");
    else if (EBUSY == status)
        printf("Mutex is locked");
}

static void wrapp_thread_error(int status, t_move move)
{
    if (0 == status)
        return;
    if (EAGAIN == status)
        printf("No resources to create another thread");
    else if (EPERM == status)
        printf("The caller does not have appropriate permission\n");
    else if (EINVAL == status && CREATE == move)
        printf("The value specified by attr is invalid.");
    else if (EINVAL == status && (JOIN == move))
        printf("The value specified by thread is not joinable\n");
    else if (ESRCH == status)
        printf("No thread could be found corresponding to that" "specified by the given thread ID, thread.");
    else if (EDEADLK == status)
        printf("A deadlock was detected or the value of" "thread specifies the calling thread.");
}

// a safe version of malloc
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

// Pthreads
// a safe version of pthread_creat
void    safe_pthread(t_move move, pthread_t *th, void *(* holder)(void *))
{
    if (move == CREATE)
        wrapp_thread_error(pthread_create(th, NULL, holder, NULL), move);
    else if (move == JOIN)
        wrapp_thread_error(pthread_join(*th, NULL), move);
    else
        printf("ERROR: Invalid move code for pthread");
}

// Mutex
// a safe versions of mutex functions
// mx stand for mutex
void    safe_mutex(t_move move, pthread_mutex_t *mx)
{
    if (move == INIT)
        wrapp_mutex_error(pthread_mutex_init(mx, NULL), move);
    else if (move == LOCK)
        wrapp_mutex_error(pthread_mutex_lock(mx), move);
    else if (move == UNLOCK)
        wrapp_mutex_error(pthread_mutex_unlock(mx), move);
    else if (move == DESTROY)
        wrapp_mutex_error(pthread_mutex_destroy(mx), move);
    else
        printf("ERROR: Invalid move code for mutex");
}
